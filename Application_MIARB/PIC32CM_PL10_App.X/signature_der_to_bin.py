from pyasn1.codec.der import decoder
from pyasn1.type.univ import Sequence
import sys

def der_to_bin(der_path, bin_path, curve_bytes=32):
    with open(der_path, 'rb') as der_file:
        der_data = der_file.read()
    sig_seq, _ = decoder.decode(der_data, asn1Spec=Sequence())
    # Get r and s integers
    r = int(sig_seq[0])
    s = int(sig_seq[1])
    # Convert to bytes, pad to proper length
    r_bytes = r.to_bytes(curve_bytes, byteorder="big")
    s_bytes = s.to_bytes(curve_bytes, byteorder="big")
    with open(bin_path, 'wb') as bin_file:
        bin_file.write(r_bytes + s_bytes)
    print(f"Converted {der_path} -> {bin_path}")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python signature_der_to_bin.py signature.der signature.bin [curve_bytes=32]")
        sys.exit(1)
    der_path = sys.argv[1]
    bin_path = sys.argv[2]
    curve_bytes = int(sys.argv[3]) if len(sys.argv) > 3 else 32
    der_to_bin(der_path, bin_path, curve_bytes)