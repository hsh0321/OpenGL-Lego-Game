Lego lego_char;

// 점프


bool lrotate = false;
bool rrotate = false;

//걷는 모션
bool walk = false;
bool bwalk = false;

double wspeed = 0.10;
int wy = 0;


bool leg_rotate = false;
bool a = false;
int mn = 0;

double spin = 0.0;

extern bool crashLegochar();
bool bjump = false;
bool ud = true;
bool rotate_camera = true;
bool run = false;
bool cUp = false, cDown = false;
bool cam2mode = false;
bool lava = false;

int lavastate = 0;
int jy = 0;
int j = 0;
int cc = 0;
int cam = 1;
float chareyeY = 3;
double lavaHeight = 0; double lavaX = 0; double lavaY = 0;


void lavaUp() {
	if (gamemode == 1) {
		if (lava == true) {
			lavaHeight += 0.005;
			if (lavastate == 0) {
				lavaX += 0.005;
				lavaY += 0.004;
				if (lavaX > 0.12 || lavaY > 0.1)lavastate = 1;
			}
			else if (lavastate == 1) {
				lavaX -= 0.005;
				lavaY -= 0.004;
				if (lavaX < -0.1 && lavaY < -0.12)lavastate = 0;
			}
		}
	}
}
void jump_idle(void) {
	if (bjump == true) {
		if (jy >= 50) {
			bjump = false;
		}
		else if (jy >= 0) {
			if (crashLegochar() == false)lego_char.locate.y += 0.3;
			else { lego_char.locate.y -= 0.3; bjump = false; }
			jy++;
		}
	}
}

void gravity_idle(void) {
	if (gamemode == 1) {
		if (lego_char.locate.y > 0 && crashLegochar() == false) {
			lego_char.locate.y -= 0.20;
			if (crashLegochar() == true) {
				lego_char.locate.y += 0.20;
				jy = 0;
			}
			//bjump = false;
		}
		else {
			jy = 0;
		}
		if (lego_char.locate.y < lavaHeight) {
			jy = 0;
			lego_char.locate = { 0,15,0 };
			lavaHeight = 0;
		}
	}
}

void walk_idle(void) {
	if (walk == true) {
		lego_char.locate.x += wspeed * sin(deg2rad(lego_char.angle.y));
		lego_char.locate.z += wspeed * cos(deg2rad(lego_char.angle.y));
		if (crashLegochar() == true) {
			lego_char.locate.x -= wspeed * sin(deg2rad(lego_char.angle.y));
			lego_char.locate.z -= wspeed * cos(deg2rad(lego_char.angle.y));
		}
	}
}

void back_walk_idle(void) {
	if (bwalk == true) {
		lego_char.locate.x -= wspeed * sin(deg2rad(lego_char.angle.y));
		lego_char.locate.z -= wspeed * cos(deg2rad(lego_char.angle.y));
		if (crashLegochar() == true) {
			lego_char.locate.x += wspeed * sin(deg2rad(lego_char.angle.y));
			lego_char.locate.z += wspeed * cos(deg2rad(lego_char.angle.y));
		}
	}
}

void leg_idle() {
	if (leg_rotate == true) {
		if (run == true) {
			if (spin < 0.001 && spin > -0.001) {
				mn++;
			}
			if (spin > 60) {
				a = true;
			}
			else if (spin < -60) {
				a = false;
			}
			if (a == false) {
				spin += 2;
			}
			else if (a == true) {
				spin -= 2;
			}
		}
		else {
			if (spin < 0.001 && spin > -0.001) {
				mn++;
			}
			if (spin > 60) {
				a = true;
			}
			else if (spin < -60) {
				a = false;
			}
			if (a == false) {
				spin += 1;
			}
			else if (a == true) {
				spin -= 1;
			}
		}
	}
	else if (leg_rotate == false) {
		if (spin < 0.001 && spin > -0.001) {
			return;
		}

		if (spin > 0.001) {
			spin -= 1;
		}
		else if (spin < 0.001) {
			spin += 1;
		}
	}
}

void camera_idle2() {
	if (gamemode == 1 && cam2mode == true) {
		if (chareyeY > 30 || chareyeY < 50) {
			if (cUp == true) {
				chareyeY -= 0.1;
			}
			else if (cDown == true) {
				chareyeY += 0.1;
			}
		}
	}
}
void camera_idle() {
	if (gamemode == 2 && rotate_camera == true) {
		phi2 += 0.1;
		eyeX2 = r2 * sin(deg2rad(theta2)) * sin(deg2rad(phi2));
		eyeY2 = r2 * cos(deg2rad(theta2));
		eyeZ2 = r2 * sin(deg2rad(theta2)) * cos(deg2rad(phi2));
	}
}


void left_rotate(void) {
	if (lrotate == true) {
		lego_char.angle.y += 1;
		if (lego_char.angle.y == 360) {
			lego_char.angle.y = 0;
		}
	}
}

void right_rotate(void) {
	if (rrotate == true) {
		lego_char.angle.y -= 1;
		if (lego_char.angle.y == 360) {
			lego_char.angle.y = 0;
		}
	}
}




#pragma once
