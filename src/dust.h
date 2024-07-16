#include <raylib.h>

#define MAX_TOUCH_POINTS 10

Vector2 Vec2Up = { 0.0, 1.0 };
Vector2 Vec2Right = { 1.0, 0.0 };

typedef struct TouchPoint {
	int id;
	Vector2 pos;
	bool active;
} TouchPoint;
