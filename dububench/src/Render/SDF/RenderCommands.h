#pragma once

#include <any>
#include <memory>
#include <variant>
#include <vector>
#include "../../Utils/Shadermath.h"

namespace omni {
struct HitInfo {
	float myDepth;
	int myMaterialID;
};

struct FBox;
struct FBoxRound;
struct FSphere;
struct OpUnionColumns;
struct Mod1;

using Variant = std::variant<std::shared_ptr<FBox>,
							 std::shared_ptr<FBoxRound>,
							 std::shared_ptr<FSphere>,

							 std::shared_ptr<OpUnionColumns>,

							 std::shared_ptr<Mod1> >;

struct Visitor {
	vec3& myPos;

	Visitor(vec3& aPos)
		: myPos(aPos) {
	}

	template <typename T>
	HitInfo operator()(T& aCommand) {
		return aCommand->Apply(myPos);
	}
};

struct FSphere {
	vec3 myPos;
	float myRadius;
	int myMaterial;

	FSphere(vec3 aPos, float aRadius, int aMaterial = 0)
		: myPos(aPos)
		, myRadius(aRadius)
		, myMaterial(aMaterial) {
	}

	HitInfo Apply(vec3& aP) {
		return {sdf::FSphere(aP - myPos, myRadius), myMaterial};
	}
};

struct FBoxRound {
	vec3 myPos;
	vec3 mySize;
	float myRadius;
	int myMaterial;

	FBoxRound(vec3 aPos, vec3 aSize, float aRadius, int aMaterial = 0)
		: myPos(aPos)
		, mySize(aSize)
		, myRadius(aRadius)
		, myMaterial(aMaterial) {
	}

	HitInfo Apply(vec3& aP) {
		return {sdf::FBoxRound(aP - myPos, mySize, myRadius), myMaterial};
	}
};

struct FBox {
	vec3 myPos;
	vec3 mySize;
	int myMaterial;

	FBox(vec3 aPos, vec3 aSize, int aMaterial = 0)
		: myPos(aPos)
		, mySize(aSize)
		, myMaterial(aMaterial) {
	}

	HitInfo Apply(vec3& aP) {
		return {sdf::FBox(aP - myPos, mySize), myMaterial};
	}
};

struct OpUnionColumns {
	Variant myCommand1;
	Variant myCommand2;
	float mySize;
	float myColumnCount;

	OpUnionColumns(Variant aCommand1, Variant aCommand2, float aSize, float aColumnCount)
		: myCommand1(aCommand1)
		, myCommand2(aCommand2)
		, mySize(aSize)
		, myColumnCount(aColumnCount) {
	}

	HitInfo Apply(vec3& aP) {
		HitInfo res1 = std::visit(Visitor{aP}, myCommand1);
		HitInfo res2 = std::visit(Visitor{aP}, myCommand2);
		return {sdf::OpUnionColumns(res1.myDepth, res2.myDepth, mySize, myColumnCount),
				res1.myDepth < res2.myDepth ? res1.myMaterialID : res2.myMaterialID};
	}
};

struct Mod1 {
	int myAxis;
	float mySize;

	Mod1(int aAxis, float aSize)
		: myAxis(aAxis)
		, mySize(aSize) {
	}

	HitInfo Apply(vec3& aP) {
		if (myAxis == 0) {
			sdf::Mod1(aP.x, mySize);
		} else if (myAxis == 1) {
			sdf::Mod1(aP.y, mySize);
		} else {
			sdf::Mod1(aP.z, mySize);
		}

		return {FLT_MAX, 0};
	}
};

struct CommandList {
	void AddCommand(Variant aCommand) {
		myCommands.push_back(aCommand);
	}

	HitInfo ApplyCommands(const vec3& aPosition) {
		vec3 pos = aPosition;

		HitInfo minInfo{FLT_MAX, 0};
		HitInfo curInfo = minInfo;

		for (Variant& command : myCommands) {
			curInfo = std::visit(Visitor{pos}, command);
			if (curInfo.myDepth < minInfo.myDepth) {
				minInfo = curInfo;
			}
		}

		return minInfo;
	}

private:
	std::vector<Variant> myCommands;
};
}  // namespace omni
