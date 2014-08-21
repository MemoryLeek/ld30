#ifndef ISTATE_H
#define ISTATE_H

class IState
{
	public:
		virtual ~IState() {}
		virtual IState *update(double delta) = 0;
};

#endif // ISTATE_H
