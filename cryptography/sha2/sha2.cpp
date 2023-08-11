#include "sha2.h"


void SHA2::init() {
    bitlen=0;
    blocklen=0;
    state[0] = 0x6a09e667;
	state[1] = 0xbb67ae85;
	state[2] = 0x3c6ef372;
	state[3] = 0xa54ff53a;
	state[4] = 0x510e527f;
	state[5] = 0x9b05688c;
	state[6] = 0x1f83d9ab;
	state[7] = 0x5be0cd19;
}


void SHA2::update(const uint8_t *data_in, size_t data_size){
    for (int i = 0; i < data_size; i++) {
        data[blocklen++] = data_in[i];
        if (blocklen == 64) {
            transform();
            bitlen += 512;
            blocklen=0;
        }
    }

}

void SHA2::transform(){
    uint32_t maj, xorA, xorE, choice, sum, newA, newE, splitted_data[64];
    uint32_t new_state[8];
    for(uint8_t i=0, j=0; i<16; i++, j+= 4){
        splitted_data[i] = (data[j] << 24) | (data[j + 1] << 16 ) | (data[j + 2] << 8) | (data[j + 3]);
    }
    //TODO
}

uint8_t* SHA2::get_hash(){
    uint8_t *hash = new uint8_t[32];
    pad();
    revert(hash);
    return hash;
}

void SHA2::pad() {
    uint64_t i = blocklen;
    data[i++] = 0x80;
    uint8_t end = 56;
    if (blocklen >= 64) end = 64;

    while(i < end) data[i++] = 0x00;
    
    if(end == 56) {
        data[i++] = 0x00;
        transform();
        memset(data, 0, 56);
    }    
    bitlen += blocklen * 8;
	data[63] = bitlen;
	data[62] = bitlen >> 8;
	data[61] = bitlen >> 16;
	data[60] = bitlen >> 24;
	data[59] = bitlen >> 32;
	data[58] = bitlen >> 40;
	data[57] = bitlen >> 48;
	data[56] = bitlen >> 56;
    transform();
}

void SHA2::revert(uint8_t *hash){
    for(uint8_t i=0; i < 4; i++) {
        for (uint8_t k = 0; k < 8; k++){
            hash[i + (k*4)] = (state[k] >> (24 - i * 8)) & 0x000000ff; 
        }
    }
}
