#ifndef COMPONENT_H
#define COMPONENT_H

class Component
{
public:
	virtual ~Component() = default;

	virtual void update() const = 0;
	virtual void cleanup() const = 0;

	int getPriority() const { return priority; }
	void setPriority(int p) { priority = p; }
private:
	int priority;
};


#endif //COMPONENT_H
