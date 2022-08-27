#ifndef UTILS_HPP
# define UTILS_HPP

# include <stdint.h>

/*
uint8_t is guaranteed to be 8 bits
uint_fast8_t is guaranteed to be >= 8 bits, much like an unsigned char
*/
typedef struct {
    uint_fast16_t x;
    uint_fast16_t y;
} vec2ui;

typedef struct {
    int_fast16_t x;
    int_fast16_t y;
} vec2i;

typedef struct {
	float	x;
	float	y;
} vec2f;


typedef struct s_rect{
	vec2i	offset;
	vec2i	bounds;

	int_fast16_t	top() const { return offset.y; }
	int_fast16_t	bottom() const { return offset.y + bounds.y; }
	int_fast16_t	left() const { return offset.x; }
	int_fast16_t	right() const { return offset.x + bounds.x; }

	int_fast16_t	width() const { return bounds.x; }
	int_fast16_t	height() const { return bounds.y; }

	bool			isIn(vec2i point) const { return (point.x >= offset.x && point.x < right()) && (point.y >= offset.y && point.y < bottom());}

} rect;

typedef enum {
	SPlayer, SEnnemy
} Source;

# endif