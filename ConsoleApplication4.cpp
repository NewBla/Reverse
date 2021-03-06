#include "stdafx.h"
#include <cstring>
#include <cstdio>
#include <assert.h>
#include <malloc.h>
#include <Windows.h>
#include <cmath>
#include <cfloat>
#include <vector>
#pragma warning(disable:4996)
class Integer
{
	//std::vector<UINT> m_vecNodes;//声明一个vector,类型为UINT
 public:
	 Integer()
	{

	}

	Integer(UINT value)
	{
		SetValue(value);
	}

	~Integer()
	{
		Clear();
	}

	void SetValue(UINT value)
	{
		Clear();

		UINT v;
		while (value > 0)
		{
			v = value % 10000;
			m_vecNodes.push_back(v);
			value /= 10000;
		}
	}

	void Clear()
	{
		m_vecNodes.clear();
	}

	void Multiply(UINT v)
	{
		UINT count = m_vecNodes.size();//获取实际数据个数.

		for (UINT i = 0; i < count; i++)
		{
			if (m_vecNodes[i])
			{
				m_vecNodes[i] *= v;//数组中的每个不为0的数乘以参数
			}
		}

		for (UINT i = 0; i < count; i++)
		{
			if (m_vecNodes[i] > 10000)//判断每个数据是否＞10000
			{
				UINT k = m_vecNodes[i] / 10000;
				m_vecNodes[i] %= 10000;//如果＞10000,则该数用它除以10000的余数代替.

				if (i < count - 1)//如果不是最后一个有效的数据.
				{
					m_vecNodes[i + 1] += k;//就把k加到后一个元素上
				}
				else
				{
					while (k > 0)
					{
						UINT vv = k % 10000;
						m_vecNodes.push_back(vv);
						k /= 10000;
					}
				}
			}
		}
	}

	void Print() const
	{
		UINT count = m_vecNodes.size();

		if (count == 0)
		{
			return;
		}

		if (m_vecNodes[count - 1] > 999)
		{
			printf("%d ", m_vecNodes[count - 1]);
		}
		else if (m_vecNodes[count - 1] > 99)
		{
			printf(" %d ", m_vecNodes[count - 1]);
		}
		else if (m_vecNodes[count - 1] > 9)
		{
			printf("  %d ", m_vecNodes[count - 1]);
		}
		else
		{
			printf("   %d ", m_vecNodes[count - 1]);
		}

		for (int i = (int)(count - 2); i >= 0; i--)
		{
			if (m_vecNodes[i] > 999)
			{
				printf("%d ", m_vecNodes[i]);
			}
			else if (m_vecNodes[i] > 99)
			{
				printf("0%d ", m_vecNodes[i]);
			}
			else if (m_vecNodes[i] > 9)
			{
				printf("00%d ", m_vecNodes[i]);
			}
			else
			{
				printf("000%d ", m_vecNodes[i]);
			}

			if (i % 10 == 0)
			{
				printf("\r\n");
			}
		}
	}

	bool SaveToFile(const char* szFileName) const
	{
		size_t count = m_vecNodes.size();

		if (count == 0)
		{
			return false;
		}

		FILE * fp = ::fopen(szFileName, "wb");
		if (!fp)
		{
			return false;
		}
		if (m_vecNodes[count - 1] > 999)
		{
			fprintf(fp, "位数: %d \r\n", (count - 1) * 4 + 4);
			fprintf(fp, "%d ", m_vecNodes[count - 1]);
		}
		else if (m_vecNodes[count - 1] > 99)
		{
			fprintf(fp, "位数: %d \r\n", (count - 1) * 4 + 3);
			fprintf(fp, " %d ", m_vecNodes[count - 1]);
		}
		else if (m_vecNodes[count - 1] > 9)
		{
			fprintf(fp, "位数: %d \r\n", (count - 1) * 4 + 2);
			fprintf(fp, "  %d ", m_vecNodes[count - 1]);
		}
		else
		{
			fprintf(fp, "位数: %d \r\n", (count - 1) * 4 + 1);
			fprintf(fp, "   %d ", m_vecNodes[count - 1]);
		}

		UINT itor = 1;

		for (int i = (int)(count - 2); i >= 0; i--)
		{
			if (m_vecNodes[i] > 999)
			{
				fprintf(fp, "%d ", m_vecNodes[i]);
			}
			else if (m_vecNodes[i] > 99)
			{
				fprintf(fp, "0%d ", m_vecNodes[i]);
			}
			else if (m_vecNodes[i] > 9)
			{
				fprintf(fp, "00%d ", m_vecNodes[i]);
			}
			else
			{
				fprintf(fp, "000%d ", m_vecNodes[i]);
			}

			if ((++itor) % 10 == 0)
			{
				fprintf(fp, "\r\n");
			}
		}

		::fclose(fp);

		ShellExecuteA(NULL, "open", szFileName, NULL, NULL, SW_SHOWNORMAL);

		return true;
	}
	std::vector<UINT> m_vecNodes;//声明一个vector,类型为UINT
};

INT main()
{
	Integer aaaa;
	aaaa.m_vecNodes.resize(0x1000000);//申请0x1000000个UINT大小的内存并全部填0.

	aaaa.SetValue(31);//把数组第1个元素设为31.
	for (UINT i = 30; i > 1; i--)
	{
		aaaa.Multiply(i);
	}
	aaaa.SaveToFile("C:\\31.txt");

	aaaa.SetValue(99999);
	for (UINT i = 99998; i > 1; i--)
	{
		aaaa.Multiply(i);
		if (i % 50 == 0)
		{
			printf("%d \r\n", i);
		}
	}

	aaaa.SaveToFile("C:\\99999.txt");
}
