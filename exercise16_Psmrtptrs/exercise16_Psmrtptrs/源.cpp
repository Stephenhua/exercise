# include <iostream>
# include <string>
# include <memory>
using namespace std;
class Report
{
private:
	std::string str;
public:
	Report(const std::string s) :str(s){ std::cout << "Oject created ! \n" << endl; }
	~Report(){ cout << "Objected deleted !\n" << endl; }
	void comment()const{ cout << str << endl; }
};
int main()
{
	{
		std::auto_ptr<Report>ps(new Report("using auto_ptr"));
		ps->comment();
	}
	{
		std::shared_ptr<Report> ps(new Report("using shared_ptr"));
		ps->comment();
	}
	{
		std::unique_ptr<Report> ps(new Report("using uniqued_ptr"));
		ps->comment();
	}
	system("pause");
	return EXIT_SUCCESS;
}