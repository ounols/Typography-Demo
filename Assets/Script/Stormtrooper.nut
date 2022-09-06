class Stormtrooper extends CSEngineScript {

	function Tick(elapsedTime) {
		local angle = gameobject.GetTransform().rotation.ToEulerAngle();
		local axis = vec3();
		axis.Set(0, 1, 0);
		gameobject.GetTransform().rotation.Rotate(Quaternion.AngleAxis(axis, 0.01));
	}

	function Init(){}
	function Destroy() {}
}
