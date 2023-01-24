#include "stepper_controller.h"

const uint8_t StepperController::HALF_WAVE_PATTERN[] = {
		0b1000,
		0b1100,
		0b0100,
		0b0110,
		0b0010,
		0b0011,
		0b0001,
		0b1001,
};

StepperController::StepperController(uint8_t a, uint8_t b, uint8_t not_a, uint8_t not_b) : coil_a(a),
																																													 coil_b(b),
																																													 coil_not_a(not_a),
																																													 coil_not_b(not_b)
{
	// set pins of coils to an output
	pinMode(a, OUTPUT);
	pinMode(b, OUTPUT);
	pinMode(not_a, OUTPUT);
	pinMode(not_b, OUTPUT);
}

void StepperController::Step(STEP_DIRECTION direction)
{
	// set step forwards or backward depending on the direction argument
	switch (direction)
	{
	case CLOCKWISE:
		step++;
		break;
	case COUNTERCLOCKWISE:
		step--;
		break;
	}

	// loop back if end of pattern is reached
	if (step < 0)
		step = 7;
	if (step > 7)
		step = 0;

	// actuate the right coils to create rotation
	digitalWrite(coil_a, HALF_WAVE_PATTERN[step] & 1);
	digitalWrite(coil_b, HALF_WAVE_PATTERN[step] & 2);
	digitalWrite(coil_not_a, HALF_WAVE_PATTERN[step] & 4);
	digitalWrite(coil_not_b, HALF_WAVE_PATTERN[step] & 8);
}

void StepperController::MoveSteps(uint64_t steps, STEP_DIRECTION direction)
{
	for (uint64_t i = 0; i < steps; i++)
	{
		Step(direction);
	}
}
