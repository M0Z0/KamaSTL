class B{
public:
	void check()
	{
		return;
	}
};

class E{
private:
	bool check() const{
		return true;
	}
};

class M :public E{

};

