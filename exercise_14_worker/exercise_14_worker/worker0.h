# ifdef WORKER0_H_
# define WORKER0_H_
# include <string>

class Worker
{
private:
	std::string fullname;
	long id;
public:
	Worker() :fullname("no one"), id(0L){}
	Worker(const std::string &s, long n) :fullname(s), id(n){}
	virtual ~Worker() = 0;
	virtual void Set();
	virtual void show() const;
};

class Waiter :public Worker
{
private:
	int panache;
public:
	Waiter() :Worker(), panache(0){}
	Waiter(const std::string & s, long s, int p = 0) :Worker(s, n), panache(p){}
	Waiter(const Worker &wk, int p = 0) :Worker(wk), panache(p){}
	void Set();
	void Show() const;
};
class Singer :public Worker
{
protected:
	enum{other,alto,contralto,soprano,bass,baritone,tenor};
	enum{Vtypes=7};
private:
	static char *pv[Vtypes];
	int voice;
public:
	Signer() :Worker(), voice(other){}
	Signer(const std::string &s, long n, int v = other) :Worker(s, n), voice(v){}
	void Set();
	void Show() const;
};

# endif