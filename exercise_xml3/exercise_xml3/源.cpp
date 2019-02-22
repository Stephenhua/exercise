#include<stdio.h>
#include<string>
#include<iostream>
#include "tinyxml2.h"  //引用头文件
using namespace std;
using namespace tinyxml2; //使用名称空间

void show_all_node(XMLElement *tempNode)
{
	while (tempNode)
	{
		cout << "<" << tempNode->Name() << ">";
		const XMLAttribute * tmp_attr = tempNode->FirstAttribute();
		while (tmp_attr)
		{
			cout << "attr" << tmp_attr->Name() << " : " << tmp_attr->Value() << ",";
			tmp_attr = tmp_attr->Next();
		}

		if (tempNode->GetText())
		{
			cout << "text =" << tempNode->GetText() << endl;
			show_all_node(tempNode->FirstChildElement());
				tempNode = tempNode->NextSiblingElement();
		}
	}
}

int main()
{
	XMLDocument doc;
	doc.LoadFile("dream.xml");
	doc.Print();
	XMLElement *root = doc.RootElement();
	cout << root->Name() << endl;
	XMLDeclaration *decl;
	decl = doc.FirstChild()->ToDeclaration();
	if (decl != NULL)
	{
		cout << decl->Value() << endl;
	}

	XMLElement *tmpnode = root->FirstChildElement();
	cout << tmpnode->Name() << endl;
	tmpnode = tmpnode->LastChildElement("LINE");
		cout << tmpnode->Name() << endl;

	tmpnode = tmpnode->PreviousSiblingElement("SPEAKER");
	if (tmpnode->GetText())
	{
		cout << tmpnode->GetText() << endl;
	}

	const XMLAttribute *attr = tmpnode->FirstAttribute();
	cout << attr->Name() << ":" << attr->Value() << endl;
	const XMLAttribute *attr2 = attr->Next();
	cout << attr->Name() << ":" << attr->Value() << endl;

	cout << tmpnode->Attribute("name") << endl;

	system("pause");
	return 0;
}