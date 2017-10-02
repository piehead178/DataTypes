
#ifdef DEBUG_MODE
#include <iostream>
#endif

template <typename t>
constexpr t max(t a, t b)
{
	return a > b ? a : b;
}

template <typename t>
constexpr t min(t a, t b)
{
	return a < b ? a : b;
}


template <typename t, t multiplicity1, t multiplicity2>
struct multiply
{
	static const t result = multiplicity1 * multiplicity2;
};

template <typename t, t numberr, t addBy>
struct add
{
	static const t result = number + addBy;
};


template <typename t>
class linkedList
{
public:
	
	//Self Explanatory
	class linkedListObject
	{
	private:	
		t data;
		linkedListObject *nextElement;
	public:
		int changeNextElement(linkedListObject *newNext)
		{
			nextElement = newNext;
			return 0;
		}
		
		linkedListObject *getNextElement()
		{
			return nextElement;
		}
		
		t getData()
		{
				return data;
		}
		
		int changeData(t newData)
		{
			data = newData;
			return 0;
		}
	};

private:
		linkedListObject *lastElement;
		linkedListObject *nextElement;
		t headerData;
		int length;
public:
	linkedList(t d)
	{
		headerData=d;
	}
	
	int insert(t dI)
	{
		if (lastElement == nullptr)
		{
			//Changes all signaficant data on the header object.
			linkedListObject *tempPointer = new linkedListObject();
			lastElement = tempPointer;
			nextElement = tempPointer;
			lastElement->changeData(dI);
		}
		else
		{
			//Changes Data
			lastElement->changeNextElement(new linkedListObject());
			lastElement = lastElement->getNextElement();
			lastElement->changeData(dI);
		}
		length++;
		return 0;
	}
	
	t returnData(int position)
	{
		//Bug Check
		if (position >= length)
		{
			#ifdef DEBUG_MODE
			std::cout << "Element in list doesn't exist!" << std::endl;
			#endif
			return 0;
		}
		if (position == 0)
		{
			return headerData;
		}
		else
		{
			return returnPointer(position - 1)->getData();
		}
	}
	
	linkedListObject *returnPointer(int position)
	{
		if (position >= length)
		{
			#ifdef DEBUG_MODE
			std::cout << "Element in list doesn't exist!" << std::endl;
			#endif
			return 0;
		}
		
		if (position == 0)
		{
			return nextElement;
		}
		else
		{
			//Finds Data than returns it.
			linkedListObject *tempPointer;
			tempPointer = nextElement;
			for (int i = 0; i < position; i++)
			{
				tempPointer = tempPointer->getNextElement();
			}
			return tempPointer;
		}
	}

	int changeData(int position, t data)
	{
		if (position >= length)
		{
			#ifdef DEBUG_MODE
			std::cout << "Element in list doesn't exist!" << std::endl;
			#endif
			return 0;
		}
		
		if (position == 0)
		{
			headerData = data;
		}
		else
		{
			//Changes Data By Indirrect Reference
			returnPointer(position - 1)->changeData(data);
		}
		return 0;
	}
	
	int deleteElement(int position)
	{
		if (position >= length)
		{
			#ifdef DEBUG_MODE
			std::cout << "Element in list doesn't exist!" << std::endl;
			#endif
			return 0;
		}
		if (position == 0)
		{
			//Prevents a possible bug
			if (nextElement == nullptr)
			{
				return 0;
			}
			else
			{
				//Rerouts Pointers
				headerData = returnData(1);
				linkedListObject *tempPointer = returnPointer(1);
				if (lastElement == nextElement)
				{
					lastElement = tempPointer;
				}
				delete nextElement;
				nextElement = tempPointer;
			}
		}
		//The General Case Didn't Work For a Position of 1.
		else if (position == 1)
		{
			linkedListObject *tempPointer = nextElement->getNextElement();
			delete nextElement;
			nextElement = tempPointer;
			if (nextElement == nullptr)
			{
				lastElement = nullptr;
			}
		}

		else
		{
			//Creates temporary pointers to remember data as deletion occurs.
			linkedListObject *tempPointer = returnPointer(position-2);
			linkedListObject *tempPointer2 = tempPointer->
				getNextElement()->getNextElement();
			delete tempPointer->getNextElement();
			tempPointer->changeNextElement(tempPointer2);
			if (tempPointer2 == nullptr)
			{
				lastElement = tempPointer;
			}
		}
		length--;
		return 0;
	}

	//Deletes all values.
	linkedList operator~()
	{
		linkedListObject *tempPointer = nextElement;
		while (tempPointer != nullptr)
		{
			linkedListObject *tempPointer2 = tempPointer->getNextElement();
			delete tempPointer;
			tempPointer = tempPointer2;
		}
		headerData = 0;
		lastElement = nullptr;
		nextElement = nullptr;
		length = 0;
		return 0;
	}
};


template <typename t,unsigned int rows, unsigned int collumms>
class matrix
{
private:
	
	template <typename T,unsigned int matrixRows,unsigned int matrixCollumms>
	struct matrixData
	{
	T data[matrixRows][matrixCollumms];
	};
	matrixData <t,rows,collumms> mainData;

	inline t *getFirstElementLocation()
	{
		return &mainData.data[0][0];
	}

public:
	static const unsigned int Rows = rows;
	static const unsigned int Collumms = collumms;

	matrix(matrixData <t,rows,collumms> data) :mainData(data) \
	{
#ifdef DEBUG_MODE
		if (rows != collumms)
		{
			std::cout << "Not a perfect square matrix! Data Loss may ocurr." << std::endl;
		}
#endif DEBUG_MODE
	}
	matrix() 
	{
#ifdef DEBUG_MODE
		if (rows != collumms)
		{
			std::cout << "Not a perfect square matrix! Data loss may ocurr." << std::endl;
		}
#endif DEBUG_MODE
	}

	inline t getElementData(unsigned int row, unsigned int collumm)
	{
		return mainData.data[row][collumm];
	}
	
	inline void changeElementData(t data, unsigned int row, unsigned int collumm)
	{
			mainData.data[row][collumm] = data;
	}

	template <typename T, unsigned int _rows, unsigned int _collumms>
	auto operator+(matrix <T,_rows,_collumms> &mat)
	{
		matrix <t,(max<unsigned int>(Rows, mat.Rows)), (max<unsigned int>(Collumms, mat.Collumms))> operatorMatrix;
		for (unsigned int row = 0; row < min<unsigned int>(Rows, mat.Rows); row++)
		{
			for (unsigned int collumm = 0; collumm < min <unsigned int>(Collumms, mat.Collumms); collumm++)
			{
				operatorMatrix.changeElementData (getElementData(row, collumm) + mat.getElementData(row, collumm),row,collumm);
			}
		}
		//These Next Parts are just here to fill in the rest of the data into the temporarry matrix.
		if (Rows != mat.Rows)
		{
			if (max<unsigned int>(Rows, mat.Rows) == Rows)
			{
				for (unsigned int row = mat.Rows; row < Rows; row++)
				{
					for (unsigned int collumm = 0; collumm < Collumms; collumm++)
					{
						operatorMatrix.changeElementData (getElementData(row, collumm),row,collumm);
					}
				}
			}
			else
			{
				for (unsigned int row = Rows; row < mat.Rows; row++)
				{
					for (unsigned int collumm = 0; collumm < mat.Collumms; collumm++)
					{
						operatorMatrix.changeElementData(mat.getElementData(row, collumm), row, collumm);
					}
				}
			}
		}
		if (Collumms != mat.Collumms)
		{
			if (max<unsigned int>(Collumms, mat.Collumms) == Collumms)
			{
				for (unsigned int row = 0; row < Rows; row++)
				{
					for (unsigned int collumm = mat.Collumms; collumm < Collumms; collumm++)
					{
						operatorMatrix.changeElementData(getElementData(row, collumm), row, collumm);
					}
				}
			}
			else
				{
					for (unsigned int row = 0; row < mat.Rows; row++)
					{
						for (unsigned int collumm = Collumms; collumm < mat.Collumms; collumm++)
						{
							operatorMatrix.changeElementData (mat.getElementData(row, collumm),row,collumm);
						}
					}
				}
			}
		//Changes null to 0 to prevent errors.
		for (unsigned int row = (min<unsigned int>(Rows, mat.Rows)); row < (max <unsigned int>(Rows, mat.Rows)); row++)
		{
			for (unsigned int collumm = (min<unsigned int>(Collumms, mat.Collumms)); collumm < (max <unsigned int>(Collumms, mat.Collumms)); collumm++)
			{
				operatorMatrix.changeElementData(0, row, collumm);
			}
		}
		return operatorMatrix;
	}

	
	template <typename T, unsigned int _rows, unsigned int _collumms>
	auto operator-(matrix <T, _rows, _collumms> &mat)
	{
		matrix <t, (max<unsigned int>(Rows, mat.Rows)), (max<unsigned int>(Collumms, mat.Collumms))> operatorMatrix;
		for (unsigned int row = 0; row < min<unsigned int>(Rows, mat.Rows); row++)
		{
			for (unsigned int collumm = 0; collumm < min <unsigned int>(Collumms, mat.Collumms); collumm++)
			{
				operatorMatrix.changeElementData(getElementData(row, collumm) - mat.getElementData(row, collumm), row, collumm);
			}
		}
		//These Next Parts are just here to fill in the rest of the data into the temporarry matrix.
		if (Rows != mat.Rows)
		{
			if (max<unsigned int>(Rows, mat.Rows) == Rows)
			{
				for (unsigned int row = mat.Rows; row < Rows; row++)
				{
					for (unsigned int collumm = 0; collumm < Collumms; collumm++)
					{
						operatorMatrix.changeElementData(getElementData(row, collumm), row, collumm);
					}
				}
			}
			else
			{
				for (unsigned int row = Rows; row < mat.Rows; row++)
				{
					for (unsigned int collumm = 0; collumm < mat.Collumms; collumm++)
					{
						operatorMatrix.changeElementData(mat.getElementData(row, collumm), row, collumm);
					}
				}
			}
		}
		if (Collumms != mat.Collumms)
		{
			if (max<unsigned int>(Collumms, mat.Collumms) == Collumms)
			{
				for (unsigned int row = 0; row < Rows; row++)
				{
					for (unsigned int collumm = mat.Collumms; collumm < Collumms; collumm++)
					{
						operatorMatrix.changeElementData(getElementData(row, collumm), row, collumm);
					}
				}
			}
			else
			{
				for (unsigned int row = 0; row < mat.Rows; row++)
				{
					for (unsigned int collumm = Collumms; collumm < mat.Collumms; collumm++)
					{
						operatorMatrix.changeElementData(mat.getElementData(row, collumm), row, collumm);
					}
				}
			}
		}
		//Changes null to 0 to prevent errors.
		for (unsigned int row = (min<unsigned int>(Rows, mat.Rows)); row < (max <unsigned int>(Rows, mat.Rows)); row++)
		{
			for (unsigned int collumm = (min<unsigned int>(Collumms, mat.Collumms)); collumm < (max <unsigned int>(Collumms, mat.Collumms)); collumm++)
			{
				operatorMatrix.changeElementData(0, row, collumm);
			}
		}
		return operatorMatrix;
	}

	template <typename _t,unsigned int _collumms,unsigned int _rows>
	auto operator* (matrix <_t,_collumms,_rows> &mat)
	{
		matrix <t,mat.Rows, Collumms> operatorMatrix;
		for (unsigned int collumm=0; collumm<Collumms; collumm++)
		{
			for (unsigned int row = 0; row < mat.Rows; row++)
			{
				//Changes operatorMatrix data to 0 to prevent bugs.
				operatorMatrix.changeElementData(0, row, collumm);
				//Copyrow navigates the rows to multiply the collumms of the second matrix.
				for (unsigned int copyRow = 0; copyRow<(min<unsigned int>(mat.Collumms,Rows)); copyRow++)
				{
					operatorMatrix.changeElementData(operatorMatrix.getElementData(row, collumm) +
						(getElementData(copyRow, collumm) * mat.getElementData(row,copyRow)), row, collumm);
				}
			}
		}
		return operatorMatrix;
	}	

	template <typename _t, unsigned int _collumms, unsigned int _rows>
	void operator*= (matrix <_t, _collumms, _rows> &mat)
	{
		t multiple[Rows][Collumms];
		//Saves data for later use.
		for (unsigned int row=0; row<Rows; row++)
		{
			for (unsigned int collumm = 0; collumm < Collumms; collumm++)
			{
				multiple[row][collumm] = getElementData(row, collumm);
			}
		}
		//See matrix operator*
		for (unsigned int collumm = 0; collumm<Collumms; collumm++)
		{
			for (unsigned int row = 0; row < mat.Rows; row++)
			{
				changeElementData(0, row, collumm);
				for (unsigned int copyRow = 0; copyRow<(min<unsigned int>(mat.Collumms, Rows)); copyRow++)
				{
					changeElementData(getElementData(row, collumm) +
						(multiple[copyRow] [collumm] * mat.getElementData(row, copyRow)), row, collumm);
				}
			}
		}
		//Changes null to 0 to prevent errors.
		for (unsigned int row = mat.Rows; row < Rows; row++)
		{
			for (unsigned int collumm = 0; collumm < Collumms; collumm++)
			{
				changeElementData(0, row, collumm);
			}
		}
		for (unsigned int row = 0; row < mat.Rows; row++)
		{
			for (unsigned int collumm = Rows; collumm < Collumms; collumm++)
			{
				changeElementData(0, row, collumm);
			}
		}
	}


	template <typename _t, unsigned int _collumms, unsigned int _rows>
    void operator+= (matrix <_t, _collumms, _rows> &mat)
	{
		for (int row = 0; row < Rows; row++)
		{
			for (int collumm = 0; collumm < Collumms; collumm++)
			{
				changeElementData(getElementData(row, collumm) + mat.getElementData(row, collumm), row, collumm);
			}
		}
#ifdef DEBUG_MODE
		for (unsigned int row = mat.Rows; row < Rows; row++)
		{
			for (unsigned int collumm = 0; collumm < Collumms; collumm++)
			{
				if (getElementData(row, collumm) != ((getElementData(row, collumm) - mat.getElementData(row, collumm) || 0)))
				{
					std::cout << "Value of Row: " << row << "Collumm: " << collumm << " is not initialized! Check your plus sign!" << std::endl;
				}
			}
		}
#endif DEBUG_MODE
	}

	template <typename _t, unsigned int _collumms, unsigned int _rows>
	void operator-= (matrix <_t, _collumms, _rows> &mat)
		{
			for (int row = 0; row < Rows; row++)
			{
				for (int collumm = 0; collumm < Collumms; collumm++)
				{
					changeElementData(getElementData(row, collumm) - mat.getElementData(row, collumm), row, collumm);
				}
			}
#ifdef DEBUG_MODE
			for (unsigned int row = mat.Rows; row < Rows; row++)
			{
				for (unsigned int collumm = 0; collumm < Collumms; collumm++)
				{
					if (getElementData(row, collumm)  != ((getElementData(row,collumm) +mat.getElementData(row, collumm) || 0)))
					{
						std::cout << "Value of Row: " << row << "Collumm: " << collumm << " is not initialized! Check your minus sign!" << std::endl;
					}
				}
			}
#endif DEBUG_MODE
		}

		template <typename _t, unsigned int _rows, unsigned int _collumms>
		void operator=(matrix <_t,_rows,_collumms>  &mat)
		{
				for (unsigned int row = 0; row < min<unsigned int>(Rows, mat.Rows); row++)
				{
					for (int unsigned collumm = 0; collumm < min<unsigned int>(Collumms, mat.Collumms); collumm++)
					{
						changeElementData(mat.getElementData(row, collumm), row, collumm);
					}
				}
			//Clears to 0 in locations that isn't copied
			for (unsigned int row = 0; row < mat.Rows; row++)
			{
				for (unsigned int collumm = mat.Collumms; collumm < Collumms; collumm++)
				{
					changeElementData(0, row, collumm);
				}
			}
			for (unsigned int row = mat.Rows; row < Rows; row++)
			{
				for (unsigned int collumm = 0; collumm < Collumms; collumm++)
				{
					changeElementData(0, row, collumm);
				}
			}
#ifdef DEBUG_MODE
			for (unsigned int row = mat.Rows; row < Rows; row++)
			{
				for (unsigned int collumm = 0; collumm < Collumms; collumm++)
				{
					if (getElementData(row, collumm) != (mat.getElementData(row, collumm) || 0))
					{
						std::cout << "Value of Row: " << row << "Collumm: " << collumm << " is not initialized! Check your equals sign!" << std::endl;
					}
				}
			}
#endif DEBUG_MODE
		}
};
