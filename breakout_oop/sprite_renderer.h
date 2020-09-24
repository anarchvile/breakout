#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <GL/glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "texture.h"
#include "shader.h"

class SpriteRenderer
{
public:
	//constructor (initialize shaders/shapes)
	SpriteRenderer(Shader &shader);
	//destructor
	~SpriteRenderer();
	//render a quad with proper texturing and coloring
	void DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0, glm::vec3 color = glm::vec3(1));
private:
	//render state
	Shader shader;
	GLuint quadVAO;
	//initialize and configure the quad's buffer and vertex attributes
	void initRenderData();
};

#endif // !SPRITE_RENDERER
