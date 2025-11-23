__forceinline void Call(const ARG_SLOT *pArguments)
{
    {
        {};
    };
    CallTargetWorker(pArguments, 0, 0);
}
__forceinline CLR_BOOL Call_RetBool(const ARG_SLOT *pArguments)
{
    {
        {};
    };
    {
        ::GCForbid __gcForbidHolder(__FUNCTION__, "D:\\Me\\OpenSource\\runtime\\src\\coreclr\\vm\\callhelpers.h", 458);
        do
        {
            CHECK _check;
            if (_check.EnterAssert())
            {
                DebugOnlyCodeHolder __debugOnlyCodeHolder;
                __debugOnlyCodeHolder.Enter();
                ;
                if (_check.Fail(ELEMENT_TYPE_BOOLEAN == -1 || ELEMENT_TYPE_BOOLEAN == m_methodSig.GetReturnType()))
                {
                    _check.Setup("", "ELEMENT_TYPE_BOOLEAN == -1 || ELEMENT_TYPE_BOOLEAN == m_methodSig.GetReturnType()", "D:\\Me\\OpenSource\\runtime\\src\\coreclr\\vm\\callhelpers.h", 458);
                    _check.Trigger("Consistency check failed");
                }
                __debugOnlyCodeHolder.Leave();
                ;
                _check.LeaveAssert();
            }
        } while (0);
    }
    ARG_SLOT retval;
    CallTargetWorker(pArguments, &retval, sizeof(retval));
    if (0 && __ReturnOK::safe_to_return())
    {
    }
    else
        return *(CLR_BOOL *)((BYTE *)(&retval));
}
__forceinline CLR_CHAR Call_RetChar(const ARG_SLOT *pArguments)
{
    {
        {};
    };
    {
        ::GCForbid __gcForbidHolder(__FUNCTION__, "D:\\Me\\OpenSource\\runtime\\src\\coreclr\\vm\\callhelpers.h", 458);
        do
        {
            CHECK _check;
            if (_check.EnterAssert())
            {
                DebugOnlyCodeHolder __debugOnlyCodeHolder;
                __debugOnlyCodeHolder.Enter();
                ;
                if (_check.Fail(ELEMENT_TYPE_CHAR == -1 || ELEMENT_TYPE_CHAR == m_methodSig.GetReturnType()))
                {
                    _check.Setup("", "ELEMENT_TYPE_CHAR == -1 || ELEMENT_TYPE_CHAR == m_methodSig.GetReturnType()", "D:\\Me\\OpenSource\\runtime\\src\\coreclr\\vm\\callhelpers.h", 458);
                    _check.Trigger("Consistency check failed");
                }
                __debugOnlyCodeHolder.Leave();
                ;
                _check.LeaveAssert();
            }
        } while (0);
    }
    ARG_SLOT retval;
    CallTargetWorker(pArguments, &retval, sizeof(retval));
    if (0 && __ReturnOK::safe_to_return())
    {
    }
    else
        return *(CLR_CHAR *)((BYTE *)(&retval));
}
__forceinline CLR_I1 Call_RetI1(const ARG_SLOT *pArguments)
{
    {
        {};
    };
    {
        ::GCForbid __gcForbidHolder(__FUNCTION__, "D:\\Me\\OpenSource\\runtime\\src\\coreclr\\vm\\callhelpers.h", 458);
        do
        {
            CHECK _check;
            if (_check.EnterAssert())
            {
                DebugOnlyCodeHolder __debugOnlyCodeHolder;
                __debugOnlyCodeHolder.Enter();
                ;
                if (_check.Fail(ELEMENT_TYPE_I1 == -1 || ELEMENT_TYPE_I1 == m_methodSig.GetReturnType()))
                {
                    _check.Setup("", "ELEMENT_TYPE_I1 == -1 || ELEMENT_TYPE_I1 == m_methodSig.GetReturnType()", "D:\\Me\\OpenSource\\runtime\\src\\coreclr\\vm\\callhelpers.h", 458);
                    _check.Trigger("Consistency check failed");
                }
                __debugOnlyCodeHolder.Leave();
                ;
                _check.LeaveAssert();
            }
        } while (0);
    }
    ARG_SLOT retval;
    CallTargetWorker(pArguments, &retval, sizeof(retval));
    if (0 && __ReturnOK::safe_to_return())
    {
    }
    else
        return *(CLR_I1 *)((BYTE *)(&retval));
}
__forceinline CLR_U1 Call_RetU1(const ARG_SLOT *pArguments)
{
    {
        {};
    };
    {
        ::GCForbid __gcForbidHolder(__FUNCTION__, "D:\\Me\\OpenSource\\runtime\\src\\coreclr\\vm\\callhelpers.h", 458);
        do
        {
            CHECK _check;
            if (_check.EnterAssert())
            {
                DebugOnlyCodeHolder __debugOnlyCodeHolder;
                __debugOnlyCodeHolder.Enter();
                ;
                if (_check.Fail(ELEMENT_TYPE_U1 == -1 || ELEMENT_TYPE_U1 == m_methodSig.GetReturnType()))
                {
                    _check.Setup("", "ELEMENT_TYPE_U1 == -1 || ELEMENT_TYPE_U1 == m_methodSig.GetReturnType()", "D:\\Me\\OpenSource\\runtime\\src\\coreclr\\vm\\callhelpers.h", 458);
                    _check.Trigger("Consistency check failed");
                }
                __debugOnlyCodeHolder.Leave();
                ;
                _check.LeaveAssert();
            }
        } while (0);
    }
    ARG_SLOT retval;
    CallTargetWorker(pArguments, &retval, sizeof(retval));
    if (0 && __ReturnOK::safe_to_return())
    {
    }
    else
        return *(CLR_U1 *)((BYTE *)(&retval));
}
__forceinline CLR_I2 Call_RetI2(const ARG_SLOT *pArguments)
{
    {
        {};
    };
    {
        ::GCForbid __gcForbidHolder(__FUNCTION__, "D:\\Me\\OpenSource\\runtime\\src\\coreclr\\vm\\callhelpers.h", 458);
        do
        {
            CHECK _check;
            if (_check.EnterAssert())
            {
                DebugOnlyCodeHolder __debugOnlyCodeHolder;
                __debugOnlyCodeHolder.Enter();
                ;
                if (_check.Fail(ELEMENT_TYPE_I2 == -1 || ELEMENT_TYPE_I2 == m_methodSig.GetReturnType()))
                {
                    _check.Setup("", "ELEMENT_TYPE_I2 == -1 || ELEMENT_TYPE_I2 == m_methodSig.GetReturnType()", "D:\\Me\\OpenSource\\runtime\\src\\coreclr\\vm\\callhelpers.h", 458);
                    _check.Trigger("Consistency check failed");
                }
                __debugOnlyCodeHolder.Leave();
                ;
                _check.LeaveAssert();
            }
        } while (0);
    }
    ARG_SLOT retval;
    CallTargetWorker(pArguments, &retval, sizeof(retval));
    if (0 && __ReturnOK::safe_to_return())
    {
    }
    else
        return *(CLR_I2 *)((BYTE *)(&retval));
}
__forceinline CLR_U2 Call_RetU2(const ARG_SLOT *pArguments)
{
    {
        {};
    };
    {
        ::GCForbid __gcForbidHolder(__FUNCTION__, "D:\\Me\\OpenSource\\runtime\\src\\coreclr\\vm\\callhelpers.h", 458);
        do
        {
            CHECK _check;
            if (_check.EnterAssert())
            {
                DebugOnlyCodeHolder __debugOnlyCodeHolder;
                __debugOnlyCodeHolder.Enter();
                ;
                if (_check.Fail(ELEMENT_TYPE_U2 == -1 || ELEMENT_TYPE_U2 == m_methodSig.GetReturnType()))
                {
                    _check.Setup("", "ELEMENT_TYPE_U2 == -1 || ELEMENT_TYPE_U2 == m_methodSig.GetReturnType()", "D:\\Me\\OpenSource\\runtime\\src\\coreclr\\vm\\callhelpers.h", 458);
                    _check.Trigger("Consistency check failed");
                }
                __debugOnlyCodeHolder.Leave();
                ;
                _check.LeaveAssert();
            }
        } while (0);
    }
    ARG_SLOT retval;
    CallTargetWorker(pArguments, &retval, sizeof(retval));
    if (0 && __ReturnOK::safe_to_return())
    {
    }
    else
        return *(CLR_U2 *)((BYTE *)(&retval));
}
__forceinline CLR_I4 Call_RetI4(const ARG_SLOT *pArguments)
{
    {
        {};
    };
    {
        ::GCForbid __gcForbidHolder(__FUNCTION__, "D:\\Me\\OpenSource\\runtime\\src\\coreclr\\vm\\callhelpers.h", 458);
        do
        {
            CHECK _check;
            if (_check.EnterAssert())
            {
                DebugOnlyCodeHolder __debugOnlyCodeHolder;
                __debugOnlyCodeHolder.Enter();
                ;
                if (_check.Fail(ELEMENT_TYPE_I4 == -1 || ELEMENT_TYPE_I4 == m_methodSig.GetReturnType()))
                {
                    _check.Setup("", "ELEMENT_TYPE_I4 == -1 || ELEMENT_TYPE_I4 == m_methodSig.GetReturnType()", "D:\\Me\\OpenSource\\runtime\\src\\coreclr\\vm\\callhelpers.h", 458);
                    _check.Trigger("Consistency check failed");
                }
                __debugOnlyCodeHolder.Leave();
                ;
                _check.LeaveAssert();
            }
        } while (0);
    }
    ARG_SLOT retval;
    CallTargetWorker(pArguments, &retval, sizeof(retval));
    if (0 && __ReturnOK::safe_to_return())
    {
    }
    else
        return *(CLR_I4 *)((BYTE *)(&retval));
}
__forceinline CLR_U4 Call_RetU4(const ARG_SLOT *pArguments)
{
    {
        {};
    };
    {
        ::GCForbid __gcForbidHolder(__FUNCTION__, "D:\\Me\\OpenSource\\runtime\\src\\coreclr\\vm\\callhelpers.h", 458);
        do
        {
            CHECK _check;
            if (_check.EnterAssert())
            {
                DebugOnlyCodeHolder __debugOnlyCodeHolder;
                __debugOnlyCodeHolder.Enter();
                ;
                if (_check.Fail(ELEMENT_TYPE_U4 == -1 || ELEMENT_TYPE_U4 == m_methodSig.GetReturnType()))
                {
                    _check.Setup("", "ELEMENT_TYPE_U4 == -1 || ELEMENT_TYPE_U4 == m_methodSig.GetReturnType()", "D:\\Me\\OpenSource\\runtime\\src\\coreclr\\vm\\callhelpers.h", 458);
                    _check.Trigger("Consistency check failed");
                }
                __debugOnlyCodeHolder.Leave();
                ;
                _check.LeaveAssert();
            }
        } while (0);
    }
    ARG_SLOT retval;
    CallTargetWorker(pArguments, &retval, sizeof(retval));
    if (0 && __ReturnOK::safe_to_return())
    {
    }
    else
        return *(CLR_U4 *)((BYTE *)(&retval));
}
__forceinline CLR_I8 Call_RetI8(const ARG_SLOT *pArguments)
{
    {
        {};
    };
    {
        ::GCForbid __gcForbidHolder(__FUNCTION__, "D:\\Me\\OpenSource\\runtime\\src\\coreclr\\vm\\callhelpers.h", 458);
        do
        {
            CHECK _check;
            if (_check.EnterAssert())
            {
                DebugOnlyCodeHolder __debugOnlyCodeHolder;
                __debugOnlyCodeHolder.Enter();
                ;
                if (_check.Fail(ELEMENT_TYPE_I8 == -1 || ELEMENT_TYPE_I8 == m_methodSig.GetReturnType()))
                {
                    _check.Setup("", "ELEMENT_TYPE_I8 == -1 || ELEMENT_TYPE_I8 == m_methodSig.GetReturnType()", "D:\\Me\\OpenSource\\runtime\\src\\coreclr\\vm\\callhelpers.h", 458);
                    _check.Trigger("Consistency check failed");
                }
                __debugOnlyCodeHolder.Leave();
                ;
                _check.LeaveAssert();
            }
        } while (0);
    }
    ARG_SLOT retval;
    CallTargetWorker(pArguments, &retval, sizeof(retval));
    if (0 && __ReturnOK::safe_to_return())
    {
    }
    else
        return *(CLR_I8 *)((BYTE *)(&retval));
}
__forceinline CLR_U8 Call_RetU8(const ARG_SLOT *pArguments)
{
    {
        {};
    };
    {
        ::GCForbid __gcForbidHolder(__FUNCTION__, "D:\\Me\\OpenSource\\runtime\\src\\coreclr\\vm\\callhelpers.h", 458);
        do
        {
            CHECK _check;
            if (_check.EnterAssert())
            {
                DebugOnlyCodeHolder __debugOnlyCodeHolder;
                __debugOnlyCodeHolder.Enter();
                ;
                if (_check.Fail(ELEMENT_TYPE_U8 == -1 || ELEMENT_TYPE_U8 == m_methodSig.GetReturnType()))
                {
                    _check.Setup("", "ELEMENT_TYPE_U8 == -1 || ELEMENT_TYPE_U8 == m_methodSig.GetReturnType()", "D:\\Me\\OpenSource\\runtime\\src\\coreclr\\vm\\callhelpers.h", 458);
                    _check.Trigger("Consistency check failed");
                }
                __debugOnlyCodeHolder.Leave();
                ;
                _check.LeaveAssert();
            }
        } while (0);
    }
    ARG_SLOT retval;
    CallTargetWorker(pArguments, &retval, sizeof(retval));
    if (0 && __ReturnOK::safe_to_return())
    {
    }
    else
        return *(CLR_U8 *)((BYTE *)(&retval));
}
__forceinline CLR_R4 Call_RetR4(const ARG_SLOT *pArguments)
{
    {
        {};
    };
    {
        ::GCForbid __gcForbidHolder(__FUNCTION__, "D:\\Me\\OpenSource\\runtime\\src\\coreclr\\vm\\callhelpers.h", 458);
        do
        {
            CHECK _check;
            if (_check.EnterAssert())
            {
                DebugOnlyCodeHolder __debugOnlyCodeHolder;
                __debugOnlyCodeHolder.Enter();
                ;
                if (_check.Fail(ELEMENT_TYPE_R4 == -1 || ELEMENT_TYPE_R4 == m_methodSig.GetReturnType()))
                {
                    _check.Setup("", "ELEMENT_TYPE_R4 == -1 || ELEMENT_TYPE_R4 == m_methodSig.GetReturnType()", "D:\\Me\\OpenSource\\runtime\\src\\coreclr\\vm\\callhelpers.h", 458);
                    _check.Trigger("Consistency check failed");
                }
                __debugOnlyCodeHolder.Leave();
                ;
                _check.LeaveAssert();
            }
        } while (0);
    }
    ARG_SLOT retval;
    CallTargetWorker(pArguments, &retval, sizeof(retval));
    if (0 && __ReturnOK::safe_to_return())
    {
    }
    else
        return *(CLR_R4 *)((BYTE *)(&retval));
}
__forceinline CLR_R8 Call_RetR8(const ARG_SLOT *pArguments)
{
    {
        {};
    };
    {
        ::GCForbid __gcForbidHolder(__FUNCTION__, "D:\\Me\\OpenSource\\runtime\\src\\coreclr\\vm\\callhelpers.h", 458);
        do
        {
            CHECK _check;
            if (_check.EnterAssert())
            {
                DebugOnlyCodeHolder __debugOnlyCodeHolder;
                __debugOnlyCodeHolder.Enter();
                ;
                if (_check.Fail(ELEMENT_TYPE_R8 == -1 || ELEMENT_TYPE_R8 == m_methodSig.GetReturnType()))
                {
                    _check.Setup("", "ELEMENT_TYPE_R8 == -1 || ELEMENT_TYPE_R8 == m_methodSig.GetReturnType()", "D:\\Me\\OpenSource\\runtime\\src\\coreclr\\vm\\callhelpers.h", 458);
                    _check.Trigger("Consistency check failed");
                }
                __debugOnlyCodeHolder.Leave();
                ;
                _check.LeaveAssert();
            }
        } while (0);
    }
    ARG_SLOT retval;
    CallTargetWorker(pArguments, &retval, sizeof(retval));
    if (0 && __ReturnOK::safe_to_return())
    {
    }
    else
        return *(CLR_R8 *)((BYTE *)(&retval));
}
__forceinline CLR_I Call_RetI(const ARG_SLOT *pArguments)
{
    {
        {};
    };
    {
        ::GCForbid __gcForbidHolder(__FUNCTION__, "D:\\Me\\OpenSource\\runtime\\src\\coreclr\\vm\\callhelpers.h", 458);
        do
        {
            CHECK _check;
            if (_check.EnterAssert())
            {
                DebugOnlyCodeHolder __debugOnlyCodeHolder;
                __debugOnlyCodeHolder.Enter();
                ;
                if (_check.Fail(ELEMENT_TYPE_I == -1 || ELEMENT_TYPE_I == m_methodSig.GetReturnType()))
                {
                    _check.Setup("", "ELEMENT_TYPE_I == -1 || ELEMENT_TYPE_I == m_methodSig.GetReturnType()", "D:\\Me\\OpenSource\\runtime\\src\\coreclr\\vm\\callhelpers.h", 458);
                    _check.Trigger("Consistency check failed");
                }
                __debugOnlyCodeHolder.Leave();
                ;
                _check.LeaveAssert();
            }
        } while (0);
    }
    ARG_SLOT retval;
    CallTargetWorker(pArguments, &retval, sizeof(retval));
    if (0 && __ReturnOK::safe_to_return())
    {
    }
    else
        return *(CLR_I *)((BYTE *)(&retval));
}
__forceinline CLR_U Call_RetU(const ARG_SLOT *pArguments)
{
    {
        {};
    };
    {
        ::GCForbid __gcForbidHolder(__FUNCTION__, "D:\\Me\\OpenSource\\runtime\\src\\coreclr\\vm\\callhelpers.h", 458);
        do
        {
            CHECK _check;
            if (_check.EnterAssert())
            {
                DebugOnlyCodeHolder __debugOnlyCodeHolder;
                __debugOnlyCodeHolder.Enter();
                ;
                if (_check.Fail(ELEMENT_TYPE_U == -1 || ELEMENT_TYPE_U == m_methodSig.GetReturnType()))
                {
                    _check.Setup("", "ELEMENT_TYPE_U == -1 || ELEMENT_TYPE_U == m_methodSig.GetReturnType()", "D:\\Me\\OpenSource\\runtime\\src\\coreclr\\vm\\callhelpers.h", 458);
                    _check.Trigger("Consistency check failed");
                }
                __debugOnlyCodeHolder.Leave();
                ;
                _check.LeaveAssert();
            }
        } while (0);
    }
    ARG_SLOT retval;
    CallTargetWorker(pArguments, &retval, sizeof(retval));
    if (0 && __ReturnOK::safe_to_return())
    {
    }
    else
        return *(CLR_U *)((BYTE *)(&retval));
}
__forceinline ARG_SLOT Call_RetArgSlot(const ARG_SLOT *pArguments)
{
    {
        {};
    };
    {
        ::GCForbid __gcForbidHolder(__FUNCTION__, "D:\\Me\\OpenSource\\runtime\\src\\coreclr\\vm\\callhelpers.h", 458);
        do
        {
            CHECK _check;
            if (_check.EnterAssert())
            {
                DebugOnlyCodeHolder __debugOnlyCodeHolder;
                __debugOnlyCodeHolder.Enter();
                ;
                if (_check.Fail(-1 == -1 || -1 == m_methodSig.GetReturnType()))
                {
                    _check.Setup("", "-1 == -1 || -1 == m_methodSig.GetReturnType()", "D:\\Me\\OpenSource\\runtime\\src\\coreclr\\vm\\callhelpers.h", 458);
                    _check.Trigger("Consistency check failed");
                }
                __debugOnlyCodeHolder.Leave();
                ;
                _check.LeaveAssert();
            }
        } while (0);
    }
    ARG_SLOT retval;
    CallTargetWorker(pArguments, &retval, sizeof(retval));
    if (0 && __ReturnOK::safe_to_return())
    {
    }
    else
        return *(ARG_SLOT *)((BYTE *)(&retval));
}
