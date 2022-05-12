#ifndef BitSet__BitSet_H
#define BitSet__BitSet_H
#include <cstdint>
#include <iosfwd>
class BitSet
{
private:
	class BitHolder;
public:

	BitSet() = default;
	BitSet(BitSet&& other);
	BitSet(const BitSet& other) //changed
	{
		int len = (other.size % 8 == 0) ? int((other.size / 8)) : int((1 + (other.size / 8)));
		set = new uint8_t [len];
		for(int i = 0; i < len; ++i)
			set[i] = other.set[i];
		size = other.size;
	}
	BitSet(const int size, const bool val = false);
	~BitSet() = default;
	BitSet& operator = (const BitSet& other);
	BitSet& operator = (BitSet&& other);
	BitSet& operator |= (const BitSet& other);
	BitSet& operator &= (const BitSet& other);
	BitSet& operator ^= (const BitSet& other);
	const BitSet operator~();
	void operator << (const int len);
	void operator >> (const int len);
	int Size () const;
	void Resize(const int size);
	void Fill(const bool val);
	BitHolder& operator [] (const int index);
	bool operator[](const int index) const;

private:
	struct BitHolder
	{
		uint8_t* byte_ptr;
		uint8_t mask;
		BitHolder() = delete;
		BitHolder(uint8_t* byte_ptr, uint8_t mask) : byte_ptr(byte_ptr), mask(mask){
			//std::cout << "bytes: " << int(*byte_ptr) << " mask: " << int(mask) << std::endl;
		};
		BitHolder(const BitHolder&) = delete;
		BitHolder(BitHolder&&) = delete;
		BitHolder& operator= (const BitHolder&) = default;
		BitHolder& operator= (BitHolder&&) = default;
		BitHolder& operator= (bool st) {
			*byte_ptr = (st) ? (*byte_ptr | mask) : (*byte_ptr & ~mask);
			return *this;
		}
		// added
		bool operator ==(bool st) const {
			uint8_t t = st ? 1 : 0;
			return ((*byte_ptr & mask) == t);
		}
		bool operator !=(bool st) const {
			return !(*this == st);
		}
		bool operator ==(const BitHolder& st) const {
			return ((*byte_ptr & mask) == (*st.byte_ptr & st.mask));
		}
		explicit operator bool() const { return ((*byte_ptr & mask) != 0); }
	};
	int size = 0;
	uint8_t* set = nullptr;
};
std::ostream& operator<<(std::ostream& ostrm, const BitSet& bs);
std::istream& operator>>(std::istream& istrm, BitSet& bs);
const BitSet operator|(const BitSet& first, const BitSet& second);
const BitSet operator&(const BitSet& first, const BitSet& second);
const BitSet operator^(const BitSet& first, const BitSet& second);
const BitSet operator^ (const BitSet& left, const BitSet& right);
const BitSet operator& (const BitSet& left, const BitSet& right);
const BitSet operator| (const BitSet& left, const BitSet& right);
#endif //BitSet__BitSet_H
