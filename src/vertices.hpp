#pragma once

#include "math/vec4.hpp"

typedef struct {
	GLfloat XYZW[4];
} Vertex;

//typedef struct {
//	GLfloat RGBA[4];
//} Color;

//const Color color_tr1[] = {
//	{ 0.7f, 0.6f, 0.9f, 1.0f }, { 0.7f, 0.6f, 0.9f, 1.0f }, { 0.7f, 0.6f, 0.9f, 1.0f }
//};
//
//const Color color_tr2[] = {
//	{ 0.7f, 0.6f, 0.9f, 1.0f }, { 0.7f, 0.6f, 0.9f, 1.0f }, { 0.7f, 0.6f, 0.9f, 1.0f }
//};
//
//const Color color_tr3[] = {
//	{ 0.7f, 0.6f, 0.9f, 1.0f }, { 0.7f, 0.6f, 0.9f, 1.0f }, { 0.7f, 0.6f, 0.9f, 1.0f }
//};
//
//const Color color_tr4[] = {
//	{ 0.7f, 0.6f, 0.9f, 1.0f }, { 0.7f, 0.6f, 0.9f, 1.0f }, { 0.7f, 0.6f, 0.9f, 1.0f }
//};
//
//const Color color_tr5[] = {
//	{ 0.7f, 0.6f, 0.9f, 1.0f }, { 0.7f, 0.6f, 0.9f, 1.0f }, { 0.7f, 0.6f, 0.9f, 1.0f }
//};
//
//const Color color_sq[] = {
//	{ 0.7f, 0.6f, 0.9f, 1.0f }, { 0.7f, 0.6f, 0.9f, 1.0f }, { 0.7f, 0.6f, 0.9f, 1.0f }, { 0.7f, 0.6f, 0.9f, 1.0f }
//};
//
//const Color color_pa[] = {
//	{ 0.7f, 0.6f, 0.9f, 1.0f }, { 0.7f, 0.6f, 0.9f, 1.0f }, { 0.7f, 0.6f, 0.9f, 1.0f }, { 0.7f, 0.6f, 0.9f, 1.0f }
//};

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

math::vec4 red(1.0f, 0.43f, 0.43f, 1.0f);
math::vec4 orange(1.0f, 0.69f, 0.45f, 1.0f);
math::vec4 yellow(1.0f, 1.0f, 0.45f, 1.0f);
math::vec4 green(0.58f, 0.91f, 0.56f, 1.0f);
math::vec4 blue(0.49f, 0.78f, 0.96f, 1.0f);
math::vec4 lilac(0.81f, 0.65f, 1.0f, 1.0f);
math::vec4 white(1.0f, 1.0f, 1.0f, 1.0f);