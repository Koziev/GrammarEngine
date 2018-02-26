using System;
using System.Collections.Generic;
using System.Linq;


class PercentFormatter
{
    public static string Percent(int top, int denominator)
    {
        float f = top * 100.0F / denominator;
        return f.ToString("##0.##", System.Globalization.CultureInfo.GetCultureInfo("ru-RU"));
    }
}
