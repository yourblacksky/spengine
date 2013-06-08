#pragma once
class SScriptHelper
{
protected:
	SScriptHelper(void);
	~SScriptHelper(void);

public:
	static SPString VariablesToString(VariableMap variables);
	static VariableMap StringToVariables(SPString stringStream);
};

