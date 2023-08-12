#include "sha2.h"
#include <iostream>


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

    for(uint8_t i=0, j=0; i< 16; i++, j+= 4){
        splitted_data[i] = (data[j] << 24) | (data[j + 1] << 16 ) | (data[j + 2] << 8) | (data[j + 3]);
    }
    for (uint8_t i = 16; i < 64; i++) {
        splitted_data[i] = sigma0(splitted_data[i-2]) + splitted_data[i-7] \
            + sigma1(splitted_data[ i-15 ]) + splitted_data[i-16];
    }
    for (uint8_t i=0; i < 64; i++) {
        maj  = majority(state[0], state[1], state[2]);
        std::cout << maj << ' ';
        xorA = rotr(state[0], 2) ^ rotr(state[0], 13) ^ rotr(state[0], 22);
        xorE = rotr(state[4], 6) ^ rotr(state[4], 11) ^ rotr(state[4], 25);
        
        choice = choose( state[4], state[5], state[6] );
        sum = splitted_data[i] + K[i] + state[7] + choice + xorE;
        
        newA = xorA + maj + sum;
        newE = state[3] + sum;
		
        state[7] = state[6];
		state[6] = state[5];
		state[5] = state[4];
		state[4] = newE;
		state[3] = state[2];
		state[2] = state[1];
		state[1] = state[0];
		state[0] = newA;
    }
}

uint32_t SHA2::choose(uint32_t a, uint32_t b, uint32_t c) {
    return (a & b) ^ (~a & c);
}
uint32_t SHA2::majority(uint32_t a, uint32_t b, uint32_t c) {
	return (a & (b | c)) | (b & c);
}
uint32_t SHA2::sigma0(uint32_t x) {
    return rotr(x, 7) ^ rotr(x, 18) ^ (x>>3);
}
uint32_t SHA2::sigma1(uint32_t x) {
    return rotr(x, 17) ^ rotr(x, 19) ^ (x >> 10);
}
uint32_t SHA2::rotr(uint32_t x, uint32_t n) {
    return (x >> n) | (x << (32 - n));
}

uint8_t* SHA2::get_hash(){
    uint8_t *hash = new uint8_t[32];
    pad();
    revert(hash);
    return hash;
}

void SHA2::pad() {
    uint64_t i = blocklen;
    uint8_t end = 64;
    if (blocklen < 56) end = 56;

    data[i++] = 0x80;
    while(i < end) data[i++] = 0x00;
     
    if(end >= 56) {
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
