#ifndef _BEHAVIOR_H
#define _BEHAVIOR_H


#include <string>
#include "aVector.h"
#include "aJoint.h"
#include "aSkeleton.h"

#include "GL/glew.h"
#include "GL/glut.h"


class BehaviorController; 

// Behavior is an abstract base class for all behaviors
class Behavior
{
public:
    Behavior(const Behavior& orig);
    virtual ~Behavior() {}
    virtual const std::string& GetName() const;

    // Given an actor and behavior parameters, return a desired velocity in world coordinates
    virtual vec3 calcDesiredVel(const BehaviorController& actor) = 0;
	virtual void display(const BehaviorController& actor) {}

protected:
    Behavior(const char* name);
    std::string m_name;
	vec3 m_actorPos;
	vec3 m_actorVel;

};

// Derived classes: Seek, Flee, Arrival, Departure, Avoid, Wander, Alignment, Separation, Cohesion, Flocking, Leader
///////////////////////////////////////////////////////////////////////////////
class Seek : public Behavior
{
public:
    Seek(const AJoint& target);
    Seek(const Seek& orig);
    virtual ~Seek();

    virtual vec3 calcDesiredVel(const BehaviorController& actor);

protected:
	const AJoint& m_Target;
};

///////////////////////////////////////////////////////////////////////////////
class Flee : public Behavior
{
public:
    Flee(const AJoint& target);
    Flee(const Flee& orig);
    virtual ~Flee();

    virtual vec3 calcDesiredVel(const BehaviorController& actor);
	
protected:
	const AJoint& m_Target;
};

///////////////////////////////////////////////////////////////////////////////
class Arrival : public Behavior
{
public:
	Arrival(const AJoint& target);
	Arrival(const Arrival& orig);
	virtual ~Arrival();

	virtual vec3 calcDesiredVel(const BehaviorController& actor);

protected:
	const AJoint& m_Target;
};


///////////////////////////////////////////////////////////////////////////////
class Departure : public Behavior
{
public:
	Departure(const AJoint& target);
	Departure(const Departure& orig);
	virtual ~Departure();

	virtual vec3 calcDesiredVel(const BehaviorController& actor);

protected:
	const AJoint& m_Target;
};


///////////////////////////////////////////////////////////////////////////////
class Obstacle
{
public:
	Obstacle() {}
	virtual ~Obstacle() {}
	double m_Radius;
	AJoint m_Center;
};


///////////////////////////////////////////////////////////////////////////////
class Avoid : public Behavior
{
public:
    Avoid(const AJoint& target, const std::vector<Obstacle>& obstacles);
    Avoid(const Avoid& orig);
    virtual ~Avoid();

    virtual vec3 calcDesiredVel(const BehaviorController& actor);
	virtual void display(const BehaviorController& actor);

protected:

    const std::vector<Obstacle>& mObstacles;
    const AJoint& m_Target;
	vec3 m_obstaclePos;
};

///////////////////////////////////////////////////////////////////////////////
class Wander : public Behavior
{
public:
	Wander();
	Wander(const Wander& orig);
	virtual ~Wander();

	virtual vec3 calcDesiredVel(const BehaviorController& actor);

public:
	// the current direction
	vec3 m_Wander;
};

///////////////////////////////////////////////////////////////////////////////
class Alignment : public Behavior
{
public:
	Alignment(const AJoint& target, const std::vector<BehaviorController>& agents);
	Alignment(const Alignment& orig);
	virtual ~Alignment();

	virtual vec3 calcDesiredVel(const BehaviorController& actor);

protected:
	const std::vector<BehaviorController>& m_AgentList;
	const AJoint& m_Target;
};

///////////////////////////////////////////////////////////////////////////////
class Separation : public Behavior
{
public:
    Separation(const AJoint& target, const std::vector<BehaviorController>& agents);
    Separation(const Separation& orig);
    virtual ~Separation();

    virtual vec3 calcDesiredVel(const BehaviorController& actor);

protected:
    const std::vector<BehaviorController>& m_AgentList;
    const AJoint& m_Target;
};

///////////////////////////////////////////////////////////////////////////////
class Cohesion : public Behavior
{
public:
    Cohesion(const std::vector<BehaviorController>& agents);
    Cohesion(const Cohesion& orig);
    virtual ~Cohesion();

    virtual vec3 calcDesiredVel(const BehaviorController& actor);

protected:
    const std::vector<BehaviorController>& m_AgentList;
};

///////////////////////////////////////////////////////////////////////////////
class Flocking : public Behavior
{
public:
    Flocking(const AJoint& target, const std::vector<BehaviorController>& agents);
    Flocking(const Flocking& orig);
    virtual ~Flocking();

    virtual vec3 calcDesiredVel(const BehaviorController& actor);

protected:
    const AJoint& m_Target;
    const std::vector<BehaviorController>& m_AgentList;
};

///////////////////////////////////////////////////////////////////////////////
class Leader : public Behavior
{
public:
    Leader(const AJoint& target, std::vector<BehaviorController>& agents);
    Leader(const Leader& orig);
    virtual ~Leader();

    virtual vec3 calcDesiredVel(const BehaviorController& actor);

protected:
    std::vector<BehaviorController>& m_AgentList;
    const AJoint& m_Target;
};

#endif