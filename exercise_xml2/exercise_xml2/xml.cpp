# include <iostream>
# include <string>
# include "tinyxml2.h"
using namespace std;
using namespace tinyxml2;

int main(int argc, char * argv[])
{
	XMLDocument doc;
	
	if (doc.LoadFile("text.xml"))
	{
		doc.Print();
		exit(1);
	}
	XMLElement *scene = doc.RootElement();
	cout << " name :" << scene->Attribute("name") << endl;

	XMLElement *surface = scene->FirstChildElement("surface");

	while (surface)
	{
		const XMLAttribute *surfaceAttr = surface->FirstAttribute();
		while (surfaceAttr)
		{
			cout << surfaceAttr->Name() << ":" << surfaceAttr->Value() << " ";
			surfaceAttr = surfaceAttr->Next();
		}
		cout << endl;

		XMLElement *surfaceChild = surface->FirstChildElement();
		while (surfaceChild)
		{
			cout << surfaceChild->Name() << "=" << surfaceChild->GetText() << endl;
			surfaceChild = surfaceChild->NextSiblingElement();
		}
		cout << endl;

		surface = surface->NextSiblingElement("surface");
	}
	doc.Print();
	system("pause");
	return 0;
	
}