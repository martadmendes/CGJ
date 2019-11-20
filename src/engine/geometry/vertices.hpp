#pragma once
#include "../include.hpp"

typedef struct {
	GLfloat XYZW[4];
} Vertex;

const Vertex tr[] =
{
	{ 0.0f, 0.0f, 0.0f, 1.0f },
	{ 1.0f, 0.0f, 0.0f, 1.0f },
	{ 0.0f, 1.0f, 0.0f, 1.0f }
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
	{ -0.5f, 0.5f, 0.0f, 1.0f }, 
	{ -0.5f, -0.5f, 0.0f, 1.0f }, 
	{ 0.5f, -0.5f, 0.0f, 1.0f },
	{ 0.5f, 0.5f, 0.0f, 1.0f }
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
	{ -0.5f, 0.5f, 0.0f, 1.0f }, 
	{ -0.85f, -0.5f, 0.0f, 1.0f }, 
	{ 0.15f, -0.5f, 0.0f, 1.0f }, 
	{ 0.5f, 0.5f, 0.0f, 1.0f }
};

const GLushort indices_pa[] =
{
	0,1,2, 0,2,3
};

const GLushort indices_pa_back[] =
{
	2,1,0, 3,2,0
};

engine::math::vec4 red(1.0f, 0.43f, 0.43f, 1.0f);
engine::math::vec4 orange(1.0f, 0.69f, 0.45f, 1.0f);
engine::math::vec4 yellow(1.0f, 1.0f, 0.45f, 1.0f);
engine::math::vec4 green(0.58f, 0.91f, 0.56f, 1.0f);
engine::math::vec4 blue(0.49f, 0.78f, 0.96f, 1.0f);
engine::math::vec4 lilac(0.81f, 0.65f, 1.0f, 1.0f);
engine::math::vec4 white(1.0f, 1.0f, 1.0f, 1.0f);

engine::math::vec4 red_back = 0.5f * red;
engine::math::vec4 orange_back = 0.5f * orange;
engine::math::vec4 yellow_back = 0.5f * yellow;
engine::math::vec4 green_back = 0.5f * green;
engine::math::vec4 blue_back = 0.5f * blue;
engine::math::vec4 lilac_back = 0.5f * lilac;
engine::math::vec4 white_back = 0.5f * white;