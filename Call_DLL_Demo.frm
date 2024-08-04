VERSION 5.00
Begin VB.Form Call_DLL_Demo 
   Caption         =   "Call_DLL_Demo"
   ClientHeight    =   3015
   ClientLeft      =   120
   ClientTop       =   465
   ClientWidth     =   4560
   LinkTopic       =   "Form1"
   ScaleHeight     =   3015
   ScaleWidth      =   4560
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Command2 
      Caption         =   "x64"
      Height          =   615
      Left            =   360
      TabIndex        =   1
      Top             =   1560
      Width           =   975
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Command1"
      Height          =   495
      Left            =   1920
      TabIndex        =   0
      Top             =   960
      Width           =   1455
   End
End
Attribute VB_Name = "Call_DLL_Demo"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Declare Function hello Lib "TheDLL.dll" ()
Private Declare Function runx64 Lib "TheDLL.dll" ()


Private Sub Command1_Click()
hello

End Sub

Private Sub Command2_Click()
runx64

End Sub
