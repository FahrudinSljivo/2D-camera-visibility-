object Forma: TForma
  Left = 0
  Top = 0
  Caption = 'Forma'
  ClientHeight = 620
  ClientWidth = 1103
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Slika: TImage
    Left = 8
    Top = 8
    Width = 961
    Height = 565
    OnMouseDown = SlikaMouseDown
    OnMouseMove = SlikaMouseMove
  end
  object LabelBrojTacaka: TLabel
    Left = 1027
    Top = 8
    Width = 58
    Height = 13
    Caption = 'Broj tacaka:'
  end
  object LabelKoordinate: TLabel
    Left = 1033
    Top = 560
    Width = 52
    Height = 13
    Caption = 'Koordinate'
  end
  object TrenutnaAkcija: TLabel
    Left = 982
    Top = 96
    Width = 78
    Height = 13
    Caption = 'Trenutna akcija:'
  end
  object EditBrojTacaka: TEdit
    Left = 1025
    Top = 27
    Width = 60
    Height = 21
    TabOrder = 0
    Text = '100'
  end
  object GenerisanjeTacaka: TButton
    Left = 1020
    Top = 54
    Width = 75
    Height = 25
    Caption = 'Generisi tacke'
    TabOrder = 1
    OnClick = GenerisanjeTacakaClick
  end
  object EditKoordinate: TEdit
    Left = 1033
    Top = 591
    Width = 73
    Height = 21
    TabOrder = 2
    Text = '(0,0)'
  end
  object DugmeProstiMnogougao: TButton
    Left = 8
    Top = 589
    Width = 97
    Height = 23
    Caption = 'Prosti mnogougao'
    TabOrder = 3
    OnClick = DugmeProstiMnogougaoClick
  end
  object Clear: TButton
    Left = 1000
    Top = 529
    Width = 95
    Height = 25
    Caption = 'Clear'
    TabOrder = 4
    OnClick = ClearClick
  end
  object ZavrsiMnogougao: TButton
    Left = 1000
    Top = 498
    Width = 95
    Height = 25
    Caption = 'Zavrsi mnogougao'
    TabOrder = 5
    OnClick = ZavrsiMnogougaoClick
  end
  object DodavanjeKamere: TRadioButton
    Left = 982
    Top = 128
    Width = 113
    Height = 17
    Caption = 'Dodavanje kamere'
    TabOrder = 6
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 488
    Top = 304
  end
end
