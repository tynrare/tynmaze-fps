#include "weapon.h"
#include "root.h"
#include <raylib.h>
#include "tynmath.h"
#include <math.h>

static Model model = {0};
static Model model_gun = {0};
static Model model_sword = {0};
static Camera camera = {0};

typedef enum WEAPON_TYPE {
	WEAPON_TYPE_SWORD = 0,
	WEAPON_TYPE_GUN,
	__WEAPON_TYPES_COUNT
} WEAPON_TYPE;

static WEAPON_TYPE weapon_type = WEAPON_TYPE_SWORD;

void set_weapon(WEAPON_TYPE type) {
	switch (type) {
		default:
		case WEAPON_TYPE_SWORD:
			model = model_sword;
			break;
		case WEAPON_TYPE_GUN:
			model = model_gun;
			break;
	}

	weapon_type = type;
}

void init_weapon() {
  model_gun = LoadModel(RES_PATH "models/gun.glb");
  model_sword = LoadModel(RES_PATH "models/sword.glb");

	float roty = 0.2;
  camera.position = (Vector3){1.0f + roty, 0.8f, 2.0f}; // Camera position
  camera.target = (Vector3){0.0f - roty, 0.4f, -2.0f};   // Camera looking at point
  camera.up = (Vector3){0.0f, 1.0f,
                        -0.0f}; // Camera up vector (rotation towards target)
  camera.fovy = 1.0f;           // Camera field-of-view Y
  camera.projection = CAMERA_ORTHOGRAPHIC;

	set_weapon(WEAPON_TYPE_SWORD);
}

void swap_weapon() {
	set_weapon((weapon_type + 1) % __WEAPON_TYPES_COUNT);
}

void draw_weapon() {
  BeginMode3D(camera);
	float rot = 0.0;
	switch (weapon_type) {
		default:
		case WEAPON_TYPE_SWORD:
			rot = sinf(GetTime() * 0.7) * 20 - 10;
			break;
		case WEAPON_TYPE_GUN:
			rot = sinf(GetTime()) * 2 + 10;
			break;
	}
  DrawModelEx(model, Vector3Zero(), (Vector3){1.0, 0.0, 0.0}, rot,
              Vector3One(), WHITE);
  EndMode3D();
}

void dispose_weapon() { UnloadModel(model); }
