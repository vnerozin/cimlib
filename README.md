# CIMLIB - Common Integer Math Library

CIMLIB is set of primitive math functions for integer radix based math. It 
simplifies radix math usage, especially in case of migration from floating 
point models or changing DSP platform. CIMLIB is easy portable to any 
DSP platform. 

Library consist from memory operation, scalar, vector and frame functions. Most 
of functions exist in signed and complex 16 bit and 32 bit versions. For easy 
debug lot of functions are implemented with saturation control.

Table 1 - Function names prefixes/suffixes

| Prefixes/suffixes | Description                        |
| ----------------- | ---------------------------------- |
| mem               | Memory operation function          |
| frm               | Frame math function                |
| sc                | Scalar math function               |
| vec               | Vector math function               |
| sat               | Result is with saturation control  |
| long              | Result is with extended precision  |

## Building

A `Makefile` is provided for GNU Make. 

Make command for **portable** platform:
```
make portable release
```

To see all available build options type:
```
make portable help
```

## Using

Scalar math example:
```c
#define RADIX     (10)
#define CONST(X)  CIMLIB_CONST_S16(X, RADIX)

int16_t z;
int16_t x = CONST(7.9);
int16_t y = CONST(4.0);

z = sc_mul_s16(x, y, RADIX);
```

Vector math example:
```c
#define RADIX     (10)
#define CONST(X)  CIMLIB_CONST_S16(X, RADIX)

int16_t z[4];
int16_t x[4] = {
    CONST(7.9), CONST(4.0), CONST(2.0), CONST(1.0)
};
int16_t y[4] = {
    CONST(2.2), CONST(3.3), CONST(1.1), CONST(0.2)
};

vec_mul_s16(z, 4, RADIX, x, y);
```

For more detailed examples, see test functions in each function's source file. 

## Test

Each function in library has simple test. To force full test use following 
command:
```
make portable test
```

## Examples

See **examples** folder for examples.
 
Available examples:
* **accel_scalar** - estimation of accelerometer total acceleration and roll, 
                     pitch and heave angles; 


## Author & Copyright

Copyright (c) 2017 Vasiliy Nerozin. See `LICENSE.md` file for licensing.

## Contacts 

vnerozin@gmail.com
