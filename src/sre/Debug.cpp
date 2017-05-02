//
// Created by morten on 04/08/16.
//

#include "sre/Debug.hpp"
#include "sre/Mesh.hpp"
#include "sre/Shader.hpp"
#include "sre/Renderer.hpp"
#include "sre/impl/GL.hpp"

#include <vector>
#include <iostream>
#include "sre/Texture.hpp"

using namespace std;

namespace sre {

    glm::vec4 Debug::color = glm::vec4(1,0,1,1);

    glm::vec4 Debug::getColor(){
        return color;
    }

    void Debug::setColor(glm::vec4 color){
        Debug::color = color;
    }

    void Debug::drawLine(glm::vec3 from, glm::vec3 to){
		vector<glm::vec3> verts = {from, to};
        drawLines(verts);
    }

    void Debug::drawLines(const std::vector<glm::vec3> &verts, MeshTopology meshTopology) {
        Mesh *mesh = Mesh::create()
                .withVertexPositions(verts)
                .withMeshTopology(meshTopology)
                .build();
        Shader* shader = Shader::getUnlit();
        shader->set("color", color);
        shader->set("tex", Texture::getWhiteTexture());
        if (Renderer::instance != nullptr){
            Renderer::instance->draw(mesh, glm::mat4(1),shader);
        }
        delete mesh;
    }

    void Debug::checkGLError() {
        for(GLenum err; (err = glGetError()) != GL_NO_ERROR;)
        {
            //Process/log the error.
            switch (err){
                case GL_INVALID_ENUM:
                    std::cerr << "GL_INVALID_ENUM"<<std::endl;
                    break;
                case GL_INVALID_VALUE:
                    std::cerr << "GL_INVALID_VALUE"<<std::endl;
                    break;
                case GL_INVALID_OPERATION:
                    std::cerr << "GL_INVALID_OPERATION"<<std::endl;
                    break;
                case GL_OUT_OF_MEMORY:
                    std::cerr << "GL_OUT_OF_MEMORY"<<std::endl;
                    break;
                case GL_INVALID_FRAMEBUFFER_OPERATION:
                    std::cerr << "GL_INVALID_FRAMEBUFFER_OPERATION"<<std::endl;
                    break;

            }
        }
    }
}