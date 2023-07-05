#version 120
uniform sampler2D currentTexture;
uniform float time;

void main() {
	vec2 coord = gl_TexCoord[0].xy;

	float factorX = 0.02 * (1 + cos(5.0 * time));
	float factorY = 0.02 * (1 - cos(5.0 * time));

	coord.x = (coord.x + factorX) / (1.0 + 2.0 * factorX);
	coord.y = (coord.y + factorY) / (1.0 + 2.0 * factorY);

	vec4 pixel_color = texture2D(currentTexture, coord);

	gl_FragColor = pixel_color;
}
