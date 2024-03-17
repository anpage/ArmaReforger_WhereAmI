class SCR_WhereAmIUI : SCR_MapUIBaseComponent
{
	protected Widget m_widget;
	protected SCR_MapToolEntry m_ToolMenuEntry;

	override void Update(float timeSlice)
	{
		if (!m_widget)
			return;

		ChimeraCharacter player = ChimeraCharacter.Cast(SCR_PlayerController.GetLocalControlledEntity());
		if (!player)
		{
			m_widget.RemoveFromHierarchy();
			return;
		}

		vector posPlayer = player.GetOrigin();

		float x, y;
		m_MapEntity.WorldToScreen(posPlayer[0], posPlayer[2], x, y, true);

		x = GetGame().GetWorkspace().DPIUnscale(x);
		y = GetGame().GetWorkspace().DPIUnscale(y);

		FrameSlot.SetPos(m_widget, x, y);
	}

	override void OnMapOpen(MapConfiguration config)
	{
		super.OnMapOpen(config);

		if (m_widget)
		{
			return;
		}

		m_widget = GetGame().GetWorkspace().CreateWidgets("{3513CA0C0C83D2E3}UI/layouts/GPS/PlayerMapIndicator.layout", m_RootWidget);

		ResourceName imageSet = "{14A14368AE7FA04D}UI/Textures/Icons/PlayerMarker.imageset";
		ImageWidget image = ImageWidget.Cast(m_widget.FindAnyWidget("Image"));
		if(image)
		{
			image.LoadImageFromSet(0, imageSet, "PlayerMarker");
			image.SetColor(Color.FromRGBA(180, 0, 0, 255));
		}
	}

	//------------------------------------------------------------------------------------------------
	override void Init()
	{
		SCR_MapToolMenuUI toolMenu = SCR_MapToolMenuUI.Cast(m_MapEntity.GetMapUIComponent(SCR_MapToolMenuUI));
		if (toolMenu)
		{
			m_ToolMenuEntry = toolMenu.RegisterToolMenuEntry("{14A14368AE7FA04D}UI/Textures/Icons/PlayerMarker.imageset", "PlayerMarker", 99);
			m_ToolMenuEntry.m_OnClick.Insert(ZoomInOnPlayer);
		}
	}

	//------------------------------------------------------------------------------------------------
	protected void ZoomInOnPlayer()
	{
		ChimeraCharacter player = ChimeraCharacter.Cast(SCR_PlayerController.GetLocalControlledEntity());
		if (!player)
		{
			return;
		}

		vector posPlayer = player.GetOrigin();

		vector mapSize = m_MapEntity.GetMapWidget().GetSizeInUnits();
		float zoomVal = mapSize[0] / (mapSize[0] * (m_MapEntity.GetMapWidget().PixelPerUnit() * 1.5));

		m_MapEntity.ZoomPanSmooth(zoomVal,posPlayer[0],posPlayer[2]);
	}
};
