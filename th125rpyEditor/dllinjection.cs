using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace th125rpyEditor
{
 
    static class th125_dll
    {
        //[DllImport("th125.dll")]
        //extern static public bool LoadInitData(StringBuilder sExePass);

        //[DllImport("th125.dll")]
        //extern static public bool SaveInitData(string sExePass);

        //[DllImport("th125.dll")]
        //extern static public bool InjectMyself(string sTargetPass, ref Initalize pInit);

        //[DllImport("th125.dll", CallingConvention = CallingConvention.Cdecl)]
        //extern static public void getErrorString(StringBuilder lpDest);

        [DllImport("th125.dll",CharSet = CharSet.Ansi)]
        extern static public void InitServer(string dll_path, string target_path);

    }
}
