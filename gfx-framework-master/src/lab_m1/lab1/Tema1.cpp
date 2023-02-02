#include "lab_m1/lab1/Tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/lab1/Transform2d.h"
#include "lab_m1/lab1/Shapes.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}

void Tema1::CreateDuck(float squareSide, glm::vec3 corner,float bottom,float height, float radius)
{
    //mallard duck
    Mesh* body = shapes2D::CreateIsoscel("body", corner, bottom, height,glm::vec3(0.3, 0, 0), true);
    AddMeshToList(body);

    Mesh* wingR = shapes2D::CreateRRangTriangle("wingR", corner, squareSide*2.5, squareSide,glm::vec3(1, 0.5, 0), true);
    AddMeshToList(wingR);

    Mesh* wingL = shapes2D::CreateLRangTriangle("wingL", corner, squareSide*2.5, squareSide, glm::vec3(1, 0.5, 0), true);
    AddMeshToList(wingL);

    Mesh* head = shapes2D::CreateCircle("head", corner, radius, glm::vec3(0, 0.5, 0),true);
    AddMeshToList(head);

    //white duck
    Mesh* body2 = shapes2D::CreateIsoscel("body2", corner, bottom, height, glm::vec3(1, 1, 1), true);
    AddMeshToList(body2);

    Mesh* wingR2 = shapes2D::CreateRRangTriangle("wingR2", corner, squareSide * 2.5, squareSide, glm::vec3(1, 1, 1), true);
    AddMeshToList(wingR2);

    Mesh* wingL2 = shapes2D::CreateLRangTriangle("wingL2", corner, squareSide * 2.5, squareSide, glm::vec3(1, 1, 1), true);
    AddMeshToList(wingL2);

    Mesh* head2 = shapes2D::CreateCircle("head2", corner, radius, glm::vec3(1, 1, 1), true);
    AddMeshToList(head2);

    //rubber duck
    Mesh* beack3 = shapes2D::CreateEchilateral("beack3", corner, squareSide, glm::vec3(1, 0.5, 0), true);
    AddMeshToList(beack3);

    Mesh* body3 = shapes2D::CreateIsoscel("body3", corner, bottom, height, glm::vec3(1, 1, 0), true);
    AddMeshToList(body3);

    Mesh* wingR3 = shapes2D::CreateRRangTriangle("wingR3", corner, squareSide * 2.5, squareSide, glm::vec3(1, 1, 0), true);
    AddMeshToList(wingR3);

    Mesh* wingL3 = shapes2D::CreateLRangTriangle("wingL3", corner, squareSide * 2.5, squareSide, glm::vec3(1, 1, 0), true);
    AddMeshToList(wingL3);

    Mesh* head3 = shapes2D::CreateCircle("head3", corner, radius, glm::vec3(1, 1, 0), true);
    AddMeshToList(head3);
}

void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    srand(time(NULL));

    glm::vec3 corner = glm::vec3(0, 0, 0);
    float squareSide = 20,height = 100,bottom = 50,radius = 20;
    // Initialize tx and ty (the translation steps)
    translateX = rand() % resolution.x;
    translateY = 0;
    //initialize cross position
    BottomX = 0;
    Bottomy = 0;
    //initialize duck properties 
    bodylength = height + radius + squareSide / 2 * sqrt(3);
    duck = rand()%3;
    // Initialize sx and sy (the scale factors)
    scaleX = 1;
    scaleY = 1;
    // Initialize angularStep
    angularStep = 0;
    flap = 1;
    //Initialize bird angle
    angle = glm::radians(90.f);
    
    while (angle == glm::radians(90.f))
    {
        angle = glm::radians((float)(rand() % 150 + 15));//random angle between 15 and 165 degrees
    }
    initialspeed = 200;
    speed = initialspeed;
    //initialize interface variables (lifes, socore, bullets)
    lifes = 3;
    bullets = 3;
    birdstate = 0;
    flighttime = 1000;
    timetofly = flighttime;
    score = 0;
    //initialize meshes
    Mesh* beack= shapes2D::CreateEchilateral("beack", corner, squareSide, glm::vec3(1, 1, 0),true);
    AddMeshToList(beack);
    CreateDuck(squareSide, corner, bottom, height, radius);
    Mesh* grass = shapes2D::CreateSquare("grass", corner, squareSide * 2, glm::vec3(0, 1, 0), true);
    AddMeshToList(grass);

    Mesh* heart = shapes2D::CreateCircle("heart", corner, radius*1.5, glm::vec3(1, 0, 0), true);
    AddMeshToList(heart);

    Mesh* frame = shapes2D::CreateSquare("frame", corner, squareSide *2, glm::vec3(1, 1, 1));
    AddMeshToList(frame);

    Mesh* scoremesh = shapes2D::CreateSquare("score", corner, squareSide * 2, glm::vec3(0, 0, 1), true);
    AddMeshToList(scoremesh);

    Mesh* corss = shapes2D::CreateCross("cross", corner, squareSide * 0.5, glm::vec3(1, 1, 1));
    AddMeshToList(corss);
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::renderUI()
{
    glm::ivec2 resolution = window->GetResolution();
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Scale(100, 2);
    RenderMesh2D(meshes["grass"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(resolution.x - 500, resolution.y - 50) * transform2D::Scale(10, 1);
    RenderMesh2D(meshes["frame"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(resolution.x - 500, resolution.y - 50) * transform2D::Scale(score, 1);
    RenderMesh2D(meshes["score"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(BottomX, Bottomy);
    RenderMesh2D(meshes["cross"], shaders["VertexColor"], modelMatrix);

    for (int i = 0; i < lifes; i++)
    {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(75 * i + 50, resolution.y - 50);
        RenderMesh2D(meshes["heart"], shaders["VertexColor"], modelMatrix);
    }
    for (int i = 0; i < bullets; i++)
    {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(75 * i + 20, resolution.y - 150);
        modelMatrix *= transform2D::Scale(1.5, 1);
        RenderMesh2D(meshes["grass"], shaders["VertexColor"], modelMatrix);
    }
}

void Tema1::renderDuck(float deltaTimeSeconds)
{
    float nangle = glm::radians(90.f) - angle;

    translateX += deltaTimeSeconds * speed * cos(angle); //+ OriginX;
    translateY += sin(angle) * deltaTimeSeconds * speed; //+ OriginY;
    glm::mat3 modelMatrix1,modelMatrix2,modelMatrix3,modelMatrix4;
    modelMatrix = glm::mat3(1);
    angularStep += deltaTimeSeconds * 3 * flap;
    if (angularStep >= 3.14/4)
    {
        flap = -1;
    }
    if (angularStep <= 0)
    {
        flap = 1;
    }
    modelMatrix *= transform2D::Translate(translateX,translateY) * transform2D::Rotate(nangle) * transform2D::Translate(25, 100);
    modelMatrix1 = glm::mat3(1);
    modelMatrix1 *= transform2D::Translate(translateX, translateY) * transform2D::Rotate(nangle) * transform2D::Translate(15, 118);
    modelMatrix2 = glm::mat3(1);
    modelMatrix2 *= transform2D::Translate(translateX, translateY) * transform2D::Rotate(nangle) * transform2D::Translate(25, 60) * transform2D::Rotate(3.14 + angularStep);
    modelMatrix3 = glm::mat3(1);
    modelMatrix3 *= transform2D::Translate(translateX, translateY) * transform2D::Rotate(nangle) * transform2D::Translate(25, 60) * transform2D::Rotate(3.14 - angularStep);
    modelMatrix4 = glm::mat3(1);
    modelMatrix4 *= transform2D::Translate(translateX, translateY) * transform2D::Rotate(nangle);
    switch (duck)
    {
    case 0:
       
        RenderMesh2D(meshes["head"], shaders["VertexColor"], modelMatrix);
        RenderMesh2D(meshes["beack"], shaders["VertexColor"], modelMatrix1);
        RenderMesh2D(meshes["wingR"], shaders["VertexColor"], modelMatrix2);
        RenderMesh2D(meshes["wingL"], shaders["VertexColor"], modelMatrix3); 
        RenderMesh2D(meshes["body"], shaders["VertexColor"], modelMatrix4);
        break;
    case 1:
        RenderMesh2D(meshes["head2"], shaders["VertexColor"], modelMatrix);
        RenderMesh2D(meshes["beack"], shaders["VertexColor"], modelMatrix1);
        RenderMesh2D(meshes["wingR2"], shaders["VertexColor"], modelMatrix2);
        RenderMesh2D(meshes["wingL2"], shaders["VertexColor"], modelMatrix3);
        RenderMesh2D(meshes["body2"], shaders["VertexColor"], modelMatrix4);
        break;
    case 2:
        RenderMesh2D(meshes["head3"], shaders["VertexColor"], modelMatrix);
        RenderMesh2D(meshes["beack3"], shaders["VertexColor"], modelMatrix1);
        RenderMesh2D(meshes["wingR3"], shaders["VertexColor"], modelMatrix2);
        RenderMesh2D(meshes["wingL3"], shaders["VertexColor"], modelMatrix3);
        RenderMesh2D(meshes["body3"], shaders["VertexColor"], modelMatrix4);
        break;
    default:
        break;
    }
    
}

void Tema1::Update(float deltaTimeSeconds)
{
    renderUI();
    glm::ivec2 resolution = window->GetResolution();
    float nangle = glm::radians(90.f) - angle;
    renderDuck(deltaTimeSeconds);
    
    if (birdstate == 0)
    {
        if (bodylength * cos(angle) + translateX > resolution.x)
        {
            angle = glm::radians(90.f) + nangle;
        }
        if (bodylength * cos(angle) + translateX <= 0)
        {
            if (angle < glm::radians(0.f) || angle > glm::radians(180.f))
            {
                angle = glm::radians(540.f) - angle;
            }
            else
            {
                angle = angle - glm::radians(90.f);
            }
        }
        if (bodylength * sin(angle) + translateY <= 0)
        {
            angle = -angle;
        }
        if (bodylength * sin(angle) + translateY > resolution.y)
        {   
            angle = -angle;
        }
    }
    
    if (angle >= glm::radians(360.f))
    {
        angle = angle - glm::radians(360.f);
    }
    if (angle <= -glm::radians(-360.f))
    {
        angle = angle + glm::radians(360.f);
    }

    if (birdstate == 0 && timetofly == 0)
    {
        birdstate = 1;
        angle = glm::radians(90.f); 
        speed = 400;
        lifes--;
    }
    if (birdstate == 1 && translateY > resolution.y)
    {
        translateX = rand() % resolution.x;
        translateY = 0;
        birdstate = 0;
        timetofly = flighttime;
        angle = glm::radians(90.f);
        while (angle == glm::radians(90.f))
        {
            angle = glm::radians((float)(rand() % 150 + 15));//random angle between 15 and 165 degrees
        }
        speed = initialspeed;
        bullets = 3;
        duck = rand() % 3;
    }
    if (birdstate == 2 && translateY < 0)
    {
        translateX = rand() % resolution.x;
        translateY = 0;
        birdstate = 0;
        timetofly = flighttime;
        angle = glm::radians(90.f);
        while (angle == glm::radians(90.f))
        {
            angle = glm::radians((float)(rand() % 150 + 15));//random angle between 15 and 165 degrees
        }
        initialspeed += 100;
        speed = initialspeed;
        bullets = 3;
        duck = rand() % 3;
    }
    
    if (birdstate ==0)
    {
        timetofly --;
    }
}


void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    glm::ivec2 resolution = window->GetResolution();
    BottomX = mouseX;
    Bottomy = resolution.y - mouseY;
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    glm::ivec2 resolution = window->GetResolution();
    // my = mouseY compared to scene scenter
    int mY = resolution.y - mouseY;
    if (button == GLFW_MOUSE_BUTTON_2 && bullets > 0 && lifes > 0)
    {
        bullets --;

        if (translateX -20< mouseX && translateY -20 < mY && mouseX < bodylength * cos(angle) + translateX + 20&& mY < bodylength * sin(angle) + translateY + 20)
        {
            birdstate = 2;
            angle = glm::radians(-90.f);
            speed = 300;
            score++;
        }
        else if (translateX -20< mouseX && translateY +20 > mY && mouseX < bodylength * cos(angle) + translateX + 20 && mY > bodylength * sin(angle) + translateY - 20)
        {
            birdstate = 2;
            angle = glm::radians(-90.f);
            speed = 300;
            score++;
        }
        else if (translateX + 20 > mouseX && translateY - 20 < mY && mouseX > bodylength * cos(angle) + translateX - 20 && mY < bodylength * sin(angle) + translateY + 20)
        {
            birdstate = 2;
            angle = glm::radians(-90.f);
            speed = 300;
            score++;
        }
        else if (translateX + 20 > mouseX && translateY + 20 > mY && mouseX > bodylength * cos(angle) + translateX - 20 && mY > bodylength * sin(angle) + translateY - 20)
        {
            birdstate = 2;
            angle = glm::radians(-90.f);
            speed = 300;
            score++;
        }
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}