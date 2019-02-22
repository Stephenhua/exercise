# include"tinyxml2.h"
# include <iostream>
# include <string>

using namespace std;
using namespace tinyxml2;

void loadXml()
{
	XMLDocument  doc;

	if (!doc.LoadFile("a.xml"))
	{
		doc.PrintError();
		exit(1);
	}
	XMLElement *root = doc.FirstChildElement();
	if (root == NULL)
	{
		cerr << "Failed to load file :No root elemnt." << endl;
		doc.Clear();

	}

	for (XMLElement * elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
	{
		const char *arr = elem->Attribute("priority");
		if (strcmp(arr, "1") == 0)
		{
			XMLElement *elem1 = elem->FirstChildElement();
			XMLNode *node = elem1->FirstChild();
			cout << node->Value() << endl;
		}
		if (strcmp(elem->Value(), "Item1") == 0)
		{
			XMLNode *node = elem->FirstChild();
			cout << node->Value() << endl;
		}

	}
}

int main(int argc ,char * argv[])
{
	loadXml();
	system("pause");
	return 0;
}