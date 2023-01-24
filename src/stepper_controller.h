#include <Arduino.h>

/**
 * Defines rotation direction of a step in a stepper motor.
 *
 * CLOCKWISE rotates the rotor in the clockwise direction.
 * COUNTERCLOCKWISE rotates the rotor in the counterclockwise direction.
 */
enum STEP_DIRECTION
{
	CLOCKWISE,
	COUNTERCLOCKWISE
};

/**
 * Class for controlling a stepper motor.
 *
 * The motor will be controlled pecificly by the half wave pattern.
 * Rotation in both direction is possible
 */
class StepperController
{
private:
	/**
	 * Stores pins to actuate in order to implement the half-wave-pattern.
	 *
	 * The half-wave-pattern consists of 8 steps which are represented by a
	 * series of 4 bits where one bit controls one coil.
	 */
	static const uint8_t HALF_WAVE_PATTERN[8];

	/**
	 * Specifies which coils to be actuated.
	 */
	int8_t step = 0;

	/**
	 * Pin for A.
	 */
	uint8_t coil_a;
	/**
	 * Pin for B.
	 */
	uint8_t coil_b;
	/**
	 * Pin for not A.
	 */
	uint8_t coil_not_a;
	/**
	 * Pin for not B.
	 */
	uint8_t coil_not_b;

public:
	/**
	 * Constructor of the StepperController class.
	 *
	 * @param a Pin of the A coil.
	 * @param b Pin of the B coil.
	 * @param not_a Pin of the not A coil.
	 * @param not_b Pin of the not B coil.
	 */
	StepperController(uint8_t a, uint8_t b, uint8_t not_a, uint8_t not_b);
	/**
	 * Rotate one step.
	 *
	 * @param direction Specifies the direction of the rotation.
	 */
	void Step(STEP_DIRECTION direction);
	/**
	 * Rotate a specific amount of steps.
	 *
	 * @param steps Specifies the amount of steps to be rotated.
	 * @param direction Specifies the direction of the rotation.
	 */
	void MoveSteps(uint64_t steps, STEP_DIRECTION direction);
};
