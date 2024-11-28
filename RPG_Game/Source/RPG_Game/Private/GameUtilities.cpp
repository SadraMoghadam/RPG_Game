// Fill out your copyright notice in the Description page of Project Settings.


#include "GameUtilities.h"

int32 UGameUtilities::GetSign(int32 Value)
{
    if (Value > 0)
    {
        return 1;
    }
    else if (Value < 0)
    {
        return -1;
    }
    return 0;
}