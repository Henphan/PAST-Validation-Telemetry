# sourced from Wiki - CRC
# https://en.wikipedia.org/wiki/Cyclic_redundancy_check#Designing_polynomials

def crc_remainder(input_bitstring, polynomial_bitstring, initial_filler):
    """Calculate the CRC remainder of a string of bits using a chosen polynomial.
    initial_filler should be '1' or '0'.
    """
    polynomial_bitstring = polynomial_bitstring.lstrip("0")
    len_input = len(input_bitstring)
    initial_padding = (len(polynomial_bitstring) - 1) * initial_filler
    input_padded_array = list(input_bitstring + initial_padding)
    while "1" in input_padded_array[:len_input]:
        cur_shift = input_padded_array.index("1")
        for i in range(len(polynomial_bitstring)):
            input_padded_array[cur_shift + i] \
            = str(int(polynomial_bitstring[i] != input_padded_array[cur_shift + i]))
    return "".join(input_padded_array)[len_input:]

def crc_check(input_bitstring, polynomial_bitstring, check_value):
    """Calculate the CRC check of a string of bits using a chosen polynomial."""
    polynomial_bitstring = polynomial_bitstring.lstrip("0")
    len_input = len(input_bitstring)
    initial_padding = check_value
    input_padded_array = list(input_bitstring + initial_padding)
    while "1" in input_padded_array[:len_input]:
        cur_shift = input_padded_array.index("1")
        for i in range(len(polynomial_bitstring)):
            input_padded_array[cur_shift + i] \
            = str(int(polynomial_bitstring[i] != input_padded_array[cur_shift + i]))
    return ("1" not in "".join(input_padded_array)[len_input:])

if __name__ == "__main__":
    remainder = crc_remainder('1111111100000000111111110000000011111111000000001111111100000000', '1010', '0')
    print(hex(int(remainder, 2)), int(remainder, 2))
    # check = crc_check('11010011101100', '1011', remainder)
    # print(check)
