# include "SDT.h"

SDT_Dict	*SDT_DictRetrieve(int ID, SDT_Dict dict)
{
	int i;

	i = 0;
	if (ID < 0)
		return NULL;
	while (i < dict.size)
	{
		if (keys[i] == ID)
			return values[i];
		i++;
	}
	return NULL;
}

SDT_Dict	*SDT_DictInit(int size);

void		 SDT_DictRemove(int ID)
{

}

void		 SDT_DictEmpty(SDT_Dict dict)
{

}

void		 SDT_DictDelete(SDT_Dict dict)
{
	SDT_DictEmpty(dict);
	free(dict);
}

void		 SDT_DictAdd(SDT_Object *object, SDT_Dict *dict);
