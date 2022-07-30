#ifndef COURSEWORK_4_1_ANGLE_HPP
#define COURSEWORK_4_1_ANGLE_HPP

class Angle
{
  private:
   double _value;

  public:
  /**
   * @brief Construct a new Angle object by degrees
   * 
   * @param value an angle in degrees
   */
   Angle(double value = 0.0) : _value(value) {}

   /**
    * @brief Return value of this angle in degrees
    */
   double degrees() const { return _value; }
};

#endif // COURSEWORK_4_1_ANGLE _HPP
