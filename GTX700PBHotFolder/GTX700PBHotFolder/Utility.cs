//Confidential
//Copyright (C) 2023 Brother Industries, Ltd. All Rights Reserved.
using System.Drawing;
using System;
using System.IO;
using System.Text;
using System.Xml.Serialization;
using System.Runtime.InteropServices;


[Serializable, StructLayout(LayoutKind.Sequential, Pack = 1, CharSet = CharSet.Ansi)]
public struct GTOPTION
{
    [MarshalAs(UnmanagedType.ByValTStr, SizeConst = FileNameLen)]
    public string   szFileName;         //Output File Name              NONE = not output file
    public int      uiCopies;           //Number of Copies              1-999

    //MainSetting
    //public byte     byMachineMode;      //Machine Mode                  0:GTX-422

    [MarshalAs(UnmanagedType.ByValTStr, SizeConst = JobNameLen)]
    public string   szJobName;          //Job Name = Document name      NONE = "No Name"
    public byte     byPlatenSize;       //Platen Size                   1:16x18 2:14x16 3:10x12 4:7x8 5:24x24 6:18x22
    public byte     byInk;              //Ink                           0:Color Only 1:White Only 2:Color+White 3:Black Only
    //public byte     byResolution;       //Resolution                    0:600dpi 1:1200dpi

    public byte     byHighlight;        //Highlight     (White)         1-9
    public byte     byMask;             //Mask          (White)         1-5
    public byte     byInkVolume;        //Ink Volume    (Color Only)    1-10
    public byte     byDoublePrint;      //Double Print  (Color Only)    0-3
    public bool     bMaterialBlack;     //Show Material as Black
   // public bool     bMultiple;          //Color Multiple Pass Printing

    //Advanced
    public bool     bTransColor;        //Transparent Color
    public int      colorTrans;         //Transparent Color
    public byte     byTolerance;        //Tolerance                     0-50
    public byte     byMinWhite;         //Minimum White                 1-6
    public byte     byChoke;            //Choke                         0-10
    //public bool     bPause;             //White/Color Pause

    public byte     bySaturation;       //Saturation                    0-40
    public byte     byBrightness;       //Brightness                    0-40
    public byte     byContrast;         //Contrast                      0-40

    public int      iCyanBalance;       //Color Balance (Cyan)          -5 +5
    public int      iMagentaBalance;    //Color Balance (Magenta)       -5 +5
    public int      iYellowBalance;     //Color Balance (Yellow)        -5 +5

    public bool     bUniPrint;          //Uni-Directional Printing

    //Other
    //public int      uiReserved1;        //Reserved
    //public int      uiReserved2;        //Reserved
    //public byte     byTransLayer;       //Transparent Layer             0:OFF 1:Create ARTR 2:Import ARTR
    [MarshalAs(UnmanagedType.ByValTStr, SizeConst = FileNameLen)]
    //public string   szTransFile;        //Import ARTR File
    public int      iBlackBalance;      //Color Balance (blacK)         -5 +5
    public bool     bEcoMode;           //Eco Mode
    //public bool     bDivide;            //2 Layer White
    //public byte     byDivideSpan;       //2 Layer White Span            0-90
    //public byte     byPauseSpan;        //White/Color Pause Span        0-90

    // GTX700PB Add
    public byte     byQuality;            //Picture quality               0:High Speed 1:Normal 2:High Quality
    public bool     bPretreatment;        //Pretreatment
    public byte     byPretreatmentVolume; //Pretreatment Level            1-10

    //Consts
    public const int FileNameLen = 260;
    public const int JobNameLen  = 128;

    public GTOPTION(int dummy)
    {
        this.szFileName     = "";
        this.uiCopies       = 1;
        //MainSetting
        //this.byMachineMode  = 0;
        this.szJobName      = "";
        this.byPlatenSize   = 2;
        this.byInk          = 2;
        //this.byResolution   = 1;
        this.byInkVolume    = 10;
        this.byHighlight    = 5;
        this.byMask         = 3;
        this.byDoublePrint  = 1;
        this.bMaterialBlack = false;
        //this.bMultiple      = false;
        //Advanced
        this.bTransColor    = false;
        this.colorTrans     = 0xFFFFFF;
        this.byTolerance    = 30;
        this.byMinWhite     = 1;
        this.byChoke        = 2;
       // this.bPause         = false;
        this.bySaturation   = 5;
        this.byBrightness   = 5;
        this.byContrast     = 5;
        this.iCyanBalance   = 0;
        this.iMagentaBalance= 0;
        this.iYellowBalance = 0;
        this.bUniPrint      = false;
        //Other
        //this.uiReserved1    = 0;
        //this.uiReserved2    = 0;
        //this.byTransLayer   = 0;
        //this.szTransFile    = "";
        this.iBlackBalance  = 0;
        this.bEcoMode       = false;
        //this.bDivide        = false;
        //this.byDivideSpan   = 20;
        //this.byPauseSpan    = 20;
        this.byQuality      = 1;
        this.bPretreatment  = true;
        this.byPretreatmentVolume = 5;

    }
}


class Utility
{
    public static TYPE LoadXML<TYPE>(string file, TYPE init)
    {
        TYPE result = init;
        try
        {
            var serializer = new XmlSerializer(typeof(TYPE));
            var sr = new StreamReader(file, new UTF8Encoding(false));
            result = (TYPE) serializer.Deserialize(sr);
            sr.Close();
        }
        catch
        { }
        return result;
    }
    public static bool LoadXML<TYPE>(string file, ref TYPE value)
    {
        bool result = false;
        try
        {
            var serializer = new XmlSerializer(typeof(TYPE));
            var sr = new StreamReader(file, new UTF8Encoding(false));
            value = (TYPE) serializer.Deserialize(sr);
            sr.Close();
            result = true;
        }
        catch
        { }
        return result;
    }
    public static bool SaveXML<TYPE>(string file, TYPE value)
    {
        bool result = false;
        try
        {
            var serializer = new XmlSerializer(typeof(TYPE));
            var sw = new StreamWriter(file, false, new UTF8Encoding(false));
            serializer.Serialize(sw, value);
            sw.Close();
            result = true;
        }
        catch
        { }
        return result;
    }
    public static bool StdoutXML<TYPE>(TYPE value)
    {
        bool result = false;
        try
        {
            var serializer = new XmlSerializer(typeof(TYPE));
            var sw = new StreamWriter(System.Console.OpenStandardOutput());
            serializer.Serialize(sw, value);
            sw.Close();
            result = true;
        }
        catch
        { }
        return result;
    }
}
