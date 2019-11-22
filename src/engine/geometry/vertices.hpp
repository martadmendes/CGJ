#pragma once
#include "../include.hpp"

typedef struct {
	GLfloat XYZ[3];
} Vertex;

const Vertex tr[] =
{
	{ 0.0f, 0.0f, 0.0f },
	{ 1.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f }
};

const GLushort indices_tr[] =
{
	0,1,2
};

const GLushort indices_tr_back[] =
{
	2,1,0
};


const Vertex sq[] =
{
	{ -0.5f, 0.5f, 0.0f }, 
	{ -0.5f, -0.5f, 0.0f }, 
	{ 0.5f, -0.5f, 0.0f },
	{ 0.5f, 0.5f, 0.0f }
};

const GLushort indices_sq[] =
{
	0,1,2, 0,2,3
};

const GLushort indices_sq_back[] =
{
	2,1,0, 3,2,0
};

const Vertex pa[] =
{
	{ -0.5f, 0.5f, 0.0f }, 
	{ -0.85f, -0.5f, 0.0f }, 
	{ 0.15f, -0.5f, 0.0f }, 
	{ 0.5f, 0.5f, 0.0f }
};

const GLushort indices_pa[] =
{
	0,1,2, 0,2,3
};

const GLushort indices_pa_back[] =
{
	2,1,0, 3,2,0
};