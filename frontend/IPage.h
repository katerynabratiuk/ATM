#pragma once

class IPage
{
public:
	virtual ~IPage() = default;

	void onEnter()
	{
		doOnEnter();
	}

	void onDigit(int digit)
	{
		doOnDigit(digit);
	}

	void onClear()
	{
		doOnClear();
	}

	void onCancel()
	{
		doOnCancel();
	}

	void onSideButton(bool rightSide, int index)
	{
		doOnSideButton(rightSide, index);
	}
private:
	virtual void doOnEnter() { return; };
	virtual void doOnDigit(int digit) { return; };
	virtual void doOnClear() { return; };
	virtual void doOnCancel() { return; };
	virtual void doOnSideButton(bool rightSide, int index) { return; };
};

Q_DECLARE_INTERFACE(IPage, "")