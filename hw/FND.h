/*
 * FND.h
 *
 *  Created on: 2022. 10. 19.
 *      Author: kccistc
 */

#ifndef SRC_HW_FND_H_
#define SRC_HW_FND_H_

#define BCDtoFND_DEV_BASE_ADDRESS 0x44A10000
#define FND_VALUE_REGISTER *(uint32_t*)(BCDtoFND_DEV_BASE_ADDRESS + 0)
#define FND_CONTROL_REGISTER *(uint32_t*)(BCDtoFND_DEV_BASE_ADDRESS + 4)

#endif /* SRC_HW_FND_H_ */
