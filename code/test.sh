#!/usr/bin/env bash

############################################################
# User-defined variables

TESTS_FILE="./files/tests.txt"
TARGET_DIR="."
APP_FILE="./debug.app"
APP_OPTIONS="-d"
BUILD_APP_CMD="make debug"
BUILD_APP_ERRMSG="Cannot build application. See log above."

############################################################

# Array in format
# [task number]="task numbers | expected result (success or fail)"
# i.e [1]="1 2 2 2 3 3 | success"
# If several tests for one task exists, each test stored in separate line
tasks=()
declare -A tasksSummary=([success]=0 [unknown]=0 [fail]=0)
debug=0
verbose=0
exit_code=0

main() {
   source "$LIBRARY_BASH/print_message.sh"
   while [ -n "$1" ]; do
      case "$1" in
      -h)
         let helpWasOpen=1
         help
         ;;
      -d)
         let debug=1
         ;;
      -v)
         let verbose=1
         ;;
      *)
         help "$@"
         exit 1
         ;;
      esac
      shift
   done
   initVariables
   printDebugMessage "ABS_DIRECTORY: ${ABS_DIRECTORY}"
   printDebugMessage "TARGET_DIR: ${TARGET_DIR}"
   cd "$ABS_DIRECTORY"
   cd "$TARGET_DIR"
   printVerboseMessage "Initalizing tasks..."
   initTasks

   printVerboseMessage "Building app..."
   local build_res
   local exitc
   buildApp build_res
   exitc=$?

   if [[ $exitc > 0 ]]; then
      printMessage "$build_res"
      if ! printErrorMessageAndAsk "$BUILD_APP_ERRMSG"; then
         exit $?
      fi
   fi
   printVerboseMessage "Running tests..."
   runTests
   printResult
}

initVariables() {
   SCRIPT_PATH="${BASH_SOURCE:-$0}"
   ABS_SCRIPT_PATH="$(realpath "${SCRIPT_PATH}")"
   ABS_DIRECTORY="$(dirname "${ABS_SCRIPT_PATH}")"
}

tasksSummaryDebug() {
   printDebugMessage "tasksSummary[success]=${tasksSummary[success]}, tasksSummary[fail]=${tasksSummary[fail]},tasksSummary[unknown]=${tasksSummary[unknown]}"

}

help() {
   if [[ -n $1 ]]; then
      echo "'$1' не поддерживается (необходимо использовать верный ключ)."
   fi

   echo
   echo "Список возможных параметров (вводить через пробел):"
   echo "-h    Вывести справку"
   echo "-d    Включить отладочную информацию"
   echo "-v    Включить более подробный вывод"
   echo
   echo "Coursework test runner. Copyright (C) 2022  Stupnikov Grigory, лицензировано под GPLv3"
   exit 0
}

# $1 is nameref for build_info
buildApp() {
   local -n build_info=$1
   build_info=$($BUILD_APP_CMD 2>&1)
}

printResult() {
   message="${BBLUE}Run result:${NC}"
   message+=$'\n'"  ${BGREEN}${tasksSummary[success]} tests passed${NC}"
   message+=$'\n'"  ${BRED}${tasksSummary[fail]} tests failed${NC}"
   if [[ $verbose == 1 ]]; then
      message+=$'\n'"  ${BGRAY}${tasksSummary[unknown]} tests N/A (was not launched or unknown error ocurred)${NC}"
   fi
   printMessage "$message"
}

runTests() {
   if [[ $debug == 1 ]]; then
      printDebugMessage "Run tests:"
      for taskId in "${!tasks[@]}"; do
         local msg="taskId: $taskId, value: ${tasks[$taskId]}"
         printDebugMessage "$msg"
      done
   fi
   for taskId in "${!tasks[@]}"; do
      data=${tasks[$taskId]}
      local i=1
      while IFS= read -r line; do
         line=$(echo $line | sed 's/#.*//g' | xargs)
         numbers=$(echo $line | cut -d'|' -f1)
         expected=$(echo $line | cut -d'|' -f2 | xargs)
         tasksSummaryDebug
         printDebugMessage "test $data"
         printDebugMessage "     expected: $expected"

         local run_info=$(echo "$numbers" | $APP_FILE $APP_OPTIONS $taskId 2>&1)
         local exitc=$?

         printDebugMessage "Running command 'echo \"$numbers\" | $APP_FILE $APP_OPTIONS $taskId 2>&1'"
         printDebugMessage "$run_info"
         printDebugMessage "     \$?=$exitc"

         let tasksSummary[unknown]-=1
         if [[ $run_info != $expected || $exitc > 0 ]]; then
            printDebugMessage "     condition: '$run_info != $expected || $exitc > 0'"
            printErrorMessage "Test #${taskId}-$i '$line' failed"
            printErrorMessage "    Run info: '$run_info'"
            printErrorMessage "${BCYAN}    Expected: '$expected'${NC}"
            printErrorMessage "    Exit code: $exitc"
            exit_code=1
            let tasksSummary[fail]+=1
         elif [[ $run_info == $expected ]]; then
            if [[ $verbose == 1 ]]; then
               printSuccessMessage "${BGREEN}Test #${taskId}-$i '$line' passed${NC}"
            fi
            let tasksSummary[success]+=1
         fi
         let ++i
      done <<<$data
   done
}

initTasks() {
   local content=$(cat $TESTS_FILE)
   local pattern='^([0-9]+):'
   local commentPattern='^#'
   local taskId
   local description
   local count=0

   printDebugMessage " Discovered tests:"
   while IFS= read -r line; do
      if [[ "$line" =~ $pattern ]]; then
         taskId=${BASH_REMATCH[1]}
      else
         description=$(echo $line | xargs) #Trim whitespaces
         if [[ $description =~ $commentPattern || -z $description ]]; then
            printDebugMessage "   comment/empty line: '$description'"
            continue
         fi
         if [[ -z ${tasks[$taskId]} ]]; then
            tasks[$taskId]=$description
         else
            tasks[$taskId]+=$'\n'"$description"
         fi
         ((++count))
         printDebugMessage "   Test for ${taskId}: '$description'"
      fi
   done <<<$content
   tasksSummary["unknown"]="${count}"
   tasksSummaryDebug
}

main "$@"
exit $exit_code
