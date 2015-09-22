#include "Misc.h"
#include "tbx.h"
DWORD ParamManager::GetSingleParam(eParam eparamType)
{
    const pb::Conf_t_param *pparam = tbx::param().get_base(eparamType);
    if(pparam)
    {
        return pparam->param->intparam();
    }
    return 0;
}

std::vector<DWORD> ParamManager::GetVecParam(eParam eparamType)
{
    const pb::Conf_t_param *pparam = tbx::param().get_base(eparamType);
    if(pparam)
    {
        return pparam->vecParam;
    }
    return std::vector<DWORD>();

}
