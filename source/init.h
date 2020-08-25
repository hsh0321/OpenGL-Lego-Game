


void init_light() {
	GLfloat ambientLight[] = { 0.1f,0.1f,0.1f,1.0f };
	GLfloat diffuseLight[] = { 0.9f,0.9f,0.9f,1.0f };
	GLfloat specularLight[] = { 0.9f,0.9f,0.9f,1.0f };
	GLfloat specularMaterial[] = { 1.0f,1.0f,1.0f,1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

	
	GLfloat ambient[] = { 0.2f,0.2f,0.2f,1.0f };
	GLfloat diffuse[] = { 0.8f,0.8f,0.8f,1.0f };
	GLfloat specular[] = { 1.0f,1.0f,1.0f,1.0f };

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 64);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void antialiase_mode(void) {
	glEnable(GL_BLEND); // Alpha blending ON
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // alpha blending 옵션

	glEnable(GL_POINT_SMOOTH); // 점 anti_aliasing
	glEnable(GL_LINE_SMOOTH); // 선
	glEnable(GL_POLYGON_SMOOTH); // 면

	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST); // Antialiasing 수준 결정
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
}


