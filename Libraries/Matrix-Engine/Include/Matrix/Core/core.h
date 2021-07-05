#ifndef ___MTRX___CORE_H
#define ___MTRX___CORE_H

#define MTRX_MIN(a, b) \
((a) < (b) ? (a) : (b))

#define MTRX_MAX(a, b) \
((a) > (b) ? (a) : (b))

#define MTRX_VERSION_MAKE(variant, major, minor, patch) \
((((uint32_t)(variant)) << 29) | (((uint32_t)(major)) << 22) | (((uint32_t)(minor)) << 12) | ((uint32_t)(patch)))

#define MTRX_VERSION_VARIANT(version) \
((uint32_t)(version) >> 29)

#define MTRX_VERSION_MAJOR(version) \
(((uint32_t)(version) >> 22) & 0x7FU)

#define MTRX_VERSION_MINOR(version) \
(((uint32_t)(version) >> 12) & 0x3FFU)

#define MTRX_VERSION_PATCH(version) \
((uint32_t)(version) & 0xFFFU)

#endif // !___MTRX___CORE_H