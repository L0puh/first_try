from cryptos import *

b = Bitcoin(testnet=True)

def get_priv_key():
    valid = False
    while not valid:
        priv = random_key()
        dec = decode_privkey(priv, 'hex')
        valid = 0 < dec < N
    return (dec, priv)


def get_pub_key(decoded_priv):
    pub = fast_multiply(G, decoded_priv)
    hex_pub = encode_pubkey(pub, 'hex')
    (x, y) = pub
    if (x % 2) == 0:
        prefix = '02'
    else: 
        prefix = '03'
    com_pub = prefix + encode(x, 16) #compressed 
    return (com_pub, hex_pub)



def main():
    dec, priv = get_priv_key()
    wif_enc_priv = encode_privkey(dec, 'wif')
    print("wif:             ", wif_enc_priv) # Wallet Import format 

    compressed_priv = decode_privkey((priv + "01"), 'hex')
    wif_com_priv = encode_privkey(compressed_priv, 'wif')
    print("wif(compressed): ", wif_com_priv) 
    

    pub, hex_pub = get_pub_key(dec)
    addr = pubkey_to_address(pub) 
    print(f"\npublic key:      {pub}\
            \naddr:            {addr}\
            \naddr compressed: {pubkey_to_address(hex_pub)}")

if "__main__" == __name__:
    main()

