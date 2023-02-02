#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"

namespace shapes2D
{


    Mesh* CreateSquare(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false) {
        glm::vec3 corner = leftBottomCorner;

        std::vector<VertexFormat> vertices =
        {
            VertexFormat(corner, color),
            VertexFormat(corner + glm::vec3(length, 0, 0), color),
            VertexFormat(corner + glm::vec3(length, length, 0), color),
            VertexFormat(corner + glm::vec3(0, length, 0), color)
        };

        Mesh* square = new Mesh(name);
        std::vector<unsigned int> indices = { 0, 1, 2, 3 };

        if (!fill) {
            square->SetDrawMode(GL_LINE_LOOP);
        }
        else {
            // Draw 2 triangles. Add the remaining 2 indices
            indices.push_back(0);
            indices.push_back(2);
        }

        square->InitFromData(vertices, indices);
        return square;
    };

    Mesh* CreateEchilateral(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false) {
        glm::vec3 corner = leftBottomCorner;

        std::vector<VertexFormat> vertices =
        {
            VertexFormat(corner, color),
            VertexFormat(corner + glm::vec3(length, 0, 0), color),
            VertexFormat(corner + glm::vec3(length / 2, length /2 * sqrt(3), 0), color),
        };

        Mesh* square = new Mesh(name);
        std::vector<unsigned int> indices = { 0, 1, 2 };

        if (!fill) {
            square->SetDrawMode(GL_LINE_LOOP);
        }
        
        square->InitFromData(vertices, indices);
        return square;
    };

    Mesh* CreateIsoscel(const std::string& name, glm::vec3 leftBottomCorner, float bottom,float height, glm::vec3 color, bool fill = false) {
        glm::vec3 corner = leftBottomCorner;

        std::vector<VertexFormat> vertices =
        {
            VertexFormat(corner, color),
            VertexFormat(corner + glm::vec3(bottom, 0, 0), color),
            VertexFormat(corner + glm::vec3(bottom / 2, height, 0), color),
        };

        Mesh* square = new Mesh(name);
        std::vector<unsigned int> indices = { 0, 1, 2 };

        if (!fill) {
            square->SetDrawMode(GL_LINE_LOOP);
        }

        square->InitFromData(vertices, indices);
        return square;
    };

    Mesh* CreateRRangTriangle(const std::string& name, glm::vec3 leftBottomCorner, float length,float length2, glm::vec3 color, bool fill = false) {
        glm::vec3 corner = leftBottomCorner;

        std::vector<VertexFormat> vertices =
        {
            VertexFormat(corner, color),
            VertexFormat(corner + glm::vec3(-length, 0, 0), color),
            VertexFormat(corner + glm::vec3(0, length2, 0), color),
        };

        Mesh* square = new Mesh(name);
        std::vector<unsigned int> indices = { 0, 1, 2 };

        if (!fill) {
            square->SetDrawMode(GL_LINE_LOOP);
        }

        square->InitFromData(vertices, indices);
        return square;
    };

    Mesh* CreateLRangTriangle(const std::string& name, glm::vec3 leftBottomCorner, float length, float length2, glm::vec3 color, bool fill = false) {
        glm::vec3 corner = leftBottomCorner;

        std::vector<VertexFormat> vertices =
        {
            VertexFormat(corner, color),
            VertexFormat(corner + glm::vec3(length, 0, 0), color),
            VertexFormat(corner + glm::vec3(0, length2, 0), color),
        };

        Mesh* square = new Mesh(name);
        std::vector<unsigned int> indices = { 0, 1, 2 };

        if (!fill) {
            square->SetDrawMode(GL_LINE_LOOP);
        }

        square->InitFromData(vertices, indices);
        return square;
    };

    Mesh* CreateCircle(const std::string& name, glm::vec3 Center, float radius, glm::vec3 color, bool fill = false) {
        glm::vec3 center = Center;

        std::vector<VertexFormat> vertices;
        std::vector<unsigned int> indices;
        for (int i = 0; i < 360; i++)
        {
            vertices.push_back(VertexFormat(center + glm::vec3(cos(i)*radius,sin(i)*radius,0), color));
        }
        Mesh* square = new Mesh(name);
        vertices.push_back(VertexFormat(center, color));

        if (!fill) {
            square->SetDrawMode(GL_LINE_LOOP);
            for (int i = 0; i < 360; i++)
            {
                indices.push_back(i);
            }
        }
        else
        {
            for (int i = 0; i < 360; i+=2)
            {
                indices.push_back(360);
                indices.push_back(i);
                indices.push_back(i+1);
            }
        }

        square->InitFromData(vertices, indices);
        return square;
    };

    Mesh* CreateCross(const std::string& name, glm::vec3 Center, float length, glm::vec3 color, bool fill = false) {
        glm::vec3 center = Center;

        std::vector<VertexFormat> vertices =
        {
            VertexFormat(center, color),
            VertexFormat(center + glm::vec3(0, length, 0), color),
            VertexFormat(center, color),
            VertexFormat(center + glm::vec3(length, 0, 0), color),
            VertexFormat(center, color),
            VertexFormat(center + glm::vec3(0, -length, 0), color),
            VertexFormat(center, color),
            VertexFormat(center + glm::vec3(-length, 0, 0), color),
            VertexFormat(center, color)
        };

        Mesh* square = new Mesh(name);
        std::vector<unsigned int> indices = { 0, 1, 2, 3, 4,5,6,7 };

        if (!fill) {
            square->SetDrawMode(GL_LINE_LOOP);
        }
        else {
            // Draw 2 triangles. Add the remaining 2 indices
            indices.push_back(0);
            indices.push_back(2);
        }

        square->InitFromData(vertices, indices);
        return square;
    };
}   

