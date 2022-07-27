#!/usr/bin/env bash

TESTS_FILE="./files/tests.txt"
APP_FILE="./debug.app"
APP_OPTIONS="-d"
BUILD_APP_CMD="make dev"
BUILD_APP_ERRMSG="Cannot build application. See log above."
# Array in format
# [task number]="task numbers | expected result (success or fail)"
# i.e [1]="1 2 2 2 3 3 | success"
# If several tests for one task exists, each test stored in separate line
tasks=()
debug=0
verbose=0
exit_code=0

source "$LIBRARY_BASH/print_message.sh"

main() {
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

   printVerboseMessage "Initalizing tasks..."
   initTasks

   printVerboseMessage "Building app..."
   local build_res
   local exitc
   buildApp build_res
   exitc=$?

   if [[ $exitc > 0 ]]; then
      printMessage "$build_res"
      if ! printErrorMessageAndAsk "[ERROR] $BUILD_APP_ERRMSG"; then
         exit $?
      fi
   fi
   printVerboseMessage "Running tests..."
   runTests
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
         printDebugMessage "test $data"
         printDebugMessage "     expected: $expected"

         local run_info=$(echo "$numbers" | $APP_FILE $APP_OPTIONS $taskId 2>&1)
         local exitc=$?

         printDebugMessage "Running command 'echo \"$numbers\" | $APP_FILE $APP_OPTIONS $taskId 2>&1'"
         printDebugMessage "$run_info"
         printDebugMessage "     \$?=$exitc"

         if [[ $run_info != $expected || $exitc > 0 ]]; then
            printDebugMessage "     condition: '$run_info != $expected || $exitc > 0'"
            printMessage "${BRED}Test #${taskId}-$i '$line' failed${NC}"
            printMessage "${BRED}    Run info: '$run_info'"
            printMessage "${BCYAN}    Expected: '$expected'${NC}"
            printMessage "${BRED}    Exit code: $exitc"
            exit_code=1
         elif [[ $verbose == 1 && $run_info == $expected ]]; then
            printMessage "${BGREEN}Test #${taskId}-$i '$line' passed${NC}"
         fi
         let ++i
      done <<<$data
   done
}

initTasks() {
   local content=$(cat $TESTS_FILE)
   local pattern='^([0-9]+):'
   local taskId
   local count=0
   local description

   printDebugMessage " Discovered tests:"
   while IFS= read -r line; do
      if [[ "$line" =~ $pattern ]]; then
         taskId=${BASH_REMATCH[1]}
      else
         description=$(echo $line | xargs) #Trim whitespaces
         if [[ -z ${tasks[$taskId]} ]]; then
            tasks[$taskId]=$description
         else
            tasks[$taskId]+=$'\n'"$description"
         fi
         printDebugMessage "   Test for ${taskId}: '$description'"
      fi
   done <<<$content
}

main "$@"
exit $exit_code
