#pragma once

#include <iostream>
#include <ctime>

using namespace std;

class Well512Random {
	enum {
		DIFFER_VALUE = 100,
	};

protected:
	unsigned long state[16];
	unsigned int index;

public:

	explicit Well512Random() {
		//�õ尪 �ڵ� ����
		index = 0;
		unsigned int s = static_cast<unsigned int>(time(NULL));

		for (int i = 0; i < 16; i++) {
			state[i] = s;
			s += s + DIFFER_VALUE;
		}
	}

	explicit Well512Random(unsigned int nSeed) {
		//�õ� ���� �޾� �ʱ�ȭ
		index = 0;
		unsigned int s = nSeed;

		for (int i = 0; i < 16; i++) {
			state[i] = s;
			s += s + DIFFER_VALUE;
		}
	}

	~Well512Random() {}

	unsigned int GetValue() {
		unsigned int a, b, c, d;

		a = state[index];
		c = state[(index + 13) & 15];
		b = a ^ c ^ (a << 16) ^ (c << 15);
		c = state[(index + 9) & 15];
		c ^= (c >> 11);
		a = state[index] = b ^ c;
		d = a ^ ((a << 5) & 0xda442d24U);
		index = (index + 15) & 15;
		a = state[index];
		state[index] = a ^ b ^ d ^ (a << 2) ^ (b << 18) ^ (c << 28);

		return state[index];
	}

	unsigned int GetValue(unsigned int nMinValue, unsigned int nMaxValue) {
		return nMinValue + (GetValue() % (nMaxValue - nMinValue));
	}

	unsigned int GetValue(unsigned int nMaxValue) {
		return GetValue() % nMaxValue;
	}
};