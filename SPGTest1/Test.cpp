#include "StdAfx.h"
#include "Test.h"
#include <SPEngine.h>
#include <List>
#include "textBox.h"
#include <string>

using namespace SPEngine;

Test::Test(void)
{
	transitionOnTime = 0.2f;
	transitionOffTime = 0.2f;
	logoPosition = 0;
	countDown = 4.0f;
}

Test::~Test(void)
{
	Unload();
}

bool Test::HandleInput( float timeDelta )
{
	if (SPInputManager::GetSingleton().GetMouse()->ButtonDown(0))
	{
		if(countDown > 2)
		{
			countDown = 2;
		}
	}
	return true;
}

bool Test::Update( float timeDelta )
{
	if (state == Active && countDown > 0)
	{
		countDown -= timeDelta;
		if(countDown >= 3)
		{
			logoPosition = 4 - countDown;
		}
		else if(countDown <= 2 && countDown >=1)
		{
			logoPosition = countDown - 1;
		}		
	}	

	if (state == Active && countDown <= 0)
	{
		ExitScreen();
		SPScreenManager::GetSingleton().CreateScreen(L"test", new Test());
		SPScreenManager::GetSingleton().Register(L"test");
	}

	return true;
}

bool Test::Draw( float timeDelta )
{
	if (!isDisplay)
	{
		return false;
	}

	SPRectangle srcRect(0, 0, 600, 700);

	SPSpriteManager::GetSingleton().RenderOnScreen(blank, NULL, SPRectangle(0,0,
		SPConfigManager::GetSingleton().GetCurrentConfig().workingWidth, 
		SPConfigManager::GetSingleton().GetCurrentConfig().workingHeight),srcRect,
		SPColor::Gray, 0, NULL);

//	SPTexturePtr tex = logo;
	//SPRectangle srcRect(0, 0, 369, 552);
	//SPRectangle rect(0, 0, 369, 552);
	//SPRectangle rect1(369, 0, 369, 552);


	//
	//pramaters
	//
	SPFontPtr font1 = SPFontManager::GetSingleton().CreateFont(L"yh_101", 30, 0, 1, 5, false, L"consolas");
	SPString text1 = L"s12 ss哈哈0%&*(%%$哈哈哈,哈哈哈哈哈sss哈，哈sss sss";
	SPFontPtr font2 = SPFontManager::GetSingleton().CreateFont(L"yh_101", 30, 0, 1, 5, false, L"consolas");
	SPString text2 = L"jjJjjjj Lily";
	SPFontPtr font3 = SPFontManager::GetSingleton().CreateFont(L"yh_101", 40, 0, 1, 5, false, L"微软雅黑");
	SPString text3 = L"How can thdi.siib.eee done.";
	SPFontPtr font4 = SPFontManager::GetSingleton().CreateFont(L"yh_101", 30, 0, 1, 5, false, L"微软雅黑");
	SPString text4 = L"这，这这这这这这JJHHJJHHJJHHJJHHJJHHJJ可怎么办啊啊啊啊,啊，啊啊";
	SPString punctuations = L"/.,\';][=-)(*&^%$#@!~`\"?><:}{？》《“：}{|+——）（*&……%￥#@！~】【’；、。，";

	//wchar_t wcs[100];
	//setlocale(LC_CTYPE, ""); //很重要，没有这一句，转换会失败
	//mbstowcs(wcs, text1.c_str(), 99);
	//wstring newword(wcs);

	textBox tBox(10, 10, 700, 600, false);

	pair<SPFontPtr, SPString> line1(font1, text1);
	pair<SPFontPtr, SPString> line2(font2, text2);
	pair<SPFontPtr, SPString> line3(font3, text3);
	pair<SPFontPtr, SPString> line4(font4, text4);

	list<pair<SPFontPtr, SPString>> textList;

	textList.push_back(line1);
	textList.push_back(line2);
	textList.push_back(line3);
	textList.push_back(line4);

	//textWriter(textList, tBox, punctuations);

	return true;
}

//bool Test::textWriter(list<pair<SPFontPtr, SPString>> textList, textBox rect, SPString punctuations) {
//
//	list<pair<pair<SPFontPtr, wstring>, D3DXVECTOR2>> lines[99];
//	int lineCounter = 0;
//	int lineHeight[99] = {0};
//	D3DXVECTOR2 curPos(0, 0);
//	wstring pun = L"/.,\';][=-)(*&^%$#@!~`\"?><:}{？》《“：}{|+——）（*&……%￥#@！~】【’；、。，";
//
//	list<pair<SPFontPtr, SPString>>::iterator it;
//	int lineWidth = 0;
//
//	//
//	//put the words into one list
//	//
//	list<pair<SPFontPtr, wstring>> textContent;
//
//	for(it = textList.begin(); it != textList.end(); it++)
//	{
//		wchar_t wcs[100];
//		setlocale(LC_CTYPE, "");
//		mbstowcs(wcs, it->second.c_str(), it->second.length());
//		if(wcs[it->second.length()] != 0)
//			wcs[it->second.length()] = 0;
//
//		for(int i = 0; wcs[i] != 0; i++)
//		{
//			wstring s = L"";
//			s.push_back(wcs[i]);
//			pair<SPFontPtr, wstring> tmpLine(it->first, s);
//			textContent.push_back(tmpLine);
//		}
//	}
//
//
//	list<pair<SPFontPtr, wstring>>::iterator wIt;
//	int counter = 0;
//	int tmp = 0;
//	tmp = textContent.size();
//
//
//	for(wIt = textContent.begin(); wIt != textContent.end(); wIt++)
//	{
//		counter++;
//
//		SPString s = (char *) _bstr_t(wIt->second.c_str());
//		setlocale(LC_ALL, "chs");
//
//		list<pair<SPFontPtr, wstring>>::iterator wItNext;
//
//		if(counter == textContent.size()-1)
//		{
//			pair<SPFontPtr, wstring> tmpEnd(wIt->first, wIt->second);
//			textContent.push_back(tmpEnd);
//		}
//		wIt++;
//		wItNext = wIt;
//		int nextIsPun = pun.find_first_of(wItNext->second);
//		wIt--;
//
//		
//		SPString sNext = (char *) _bstr_t(wItNext->second.c_str());
//		setlocale(LC_ALL, "chs");
//
//		
//		if(lineWidth <= (rect.getWidth()-(wIt->first->GetWidth()+rect.getWDis()))
//			&& lineWidth > (rect.getWidth()-2*(wIt->first->GetWidth()+rect.getWDis()))
//			&& nextIsPun != wstring::npos && pun.find_first_of(wIt->second) == wstring::npos)
//		{
//			curPos.y += lineHeight[lineCounter++];
//			lineWidth = 0;
//			curPos.x = 0;
//			wIt--;
//			counter--;
//		}
//		
//		else if(lineWidth <= (rect.getWidth()-(wIt->first->GetWidth()+rect.getWDis())))
//		{
//			
//			SPFontPtr newFont = wIt->first;
//
//			pair<SPFontPtr, wstring> word1(newFont, wIt->second);
//			pair<pair<SPFontPtr, wstring>, D3DXVECTOR2> word2(word1, curPos);
//			lines[lineCounter].push_back(word2);
//
//			if(newFont.get()->GetTextSize(s).y > lineHeight[lineCounter])
//			{
//				lineHeight[lineCounter] = newFont.get()->GetTextSize(s).y;
//			}
//
//			if(newFont.get()->GetTextSize(s).x == 0)
//			{
//				curPos.x += (newFont.get()->GetWidth()+rect.getWDis());
//				lineWidth += (newFont.get()->GetWidth()+rect.getWDis());
//			}
//			else
//			{
//				curPos.x += (newFont.get()->GetTextSize(s).x+rect.getWDis());
//				lineWidth += (newFont.get()->GetTextSize(s).x+rect.getWDis());
//			}
//			if(lineWidth >= (rect.getWidth()-2*(wIt->first->GetTextSize(sNext).x+rect.getWDis()))
//				&& sNext.size() == 1 && s.size() == 1 && sNext != " " && s != " "
//				&& nextIsPun == wstring::npos && pun.find_first_of(wIt->second) == wstring::npos)
//			{
//				SPFontPtr newFont = wIt->first;
//
//				pair<SPFontPtr, wstring> word1(newFont, L"-");
//				pair<pair<SPFontPtr, wstring>, D3DXVECTOR2> word2(word1, curPos);
//				lines[lineCounter].push_back(word2);
//				curPos.y += lineHeight[lineCounter++];
//				lineWidth = 0;
//				curPos.x = 0;
//				/*wIt--;
//				counter--;*/
//			}
//		}
//		else if(wIt != textContent.begin())
//		{
//			curPos.y += lineHeight[lineCounter++];
//			lineWidth = 0;
//			curPos.x = 0;
//			wIt--;
//			counter--;
//
//		}
//		
//		if(counter == tmp){
//			break;
//		}
//	}
//		
//	
//
//	//
//	//put the words into lines, contains the font, position and the content.
//	//
//
//	/*for(it = textList.begin(); it!= textList.end(); it++) 
//	{
//		wchar_t wcs[100];
//		setlocale(LC_CTYPE, ""); //很重要，没有这一句，转换会失败
//		mbstowcs(wcs, it->second.c_str(), it->second.length());
//		if(wcs[it->second.length()] != 0)
//			wcs[it->second.length()] = 0;
//		
//		for(int i = 0; wcs[i] != 0; i++)
//		{
//			wstring content = L"";
//			content.push_back(wcs[i]);
//			SPString s = (char *) _bstr_t(content.c_str());
//			setlocale(LC_ALL, "chs");
//
//			//
//			//deal with punctuations
//			//
//			if(i > 0 && wcs[i] != 0)
//			{
//				wstring sNex = L"";
//				sNex.push_back(wcs[i+1]);
//				SPString sN = (char *) _bstr_t(sNex.c_str());
//				setlocale(LC_ALL, "chs");
//				int a = 0;
//				int b = 0;
//				a = rect.getWidth()-3*(it->first->GetTextSize(sN).x+rect.getWDis());
//				b = rect.getWidth()-2*(it->first->GetTextSize(sN).x+rect.getWDis());
//				if(lineWidth > (rect.getWidth()-3*(it->first->GetTextSize(sN).x+rect.getWDis())) &&
//					lineWidth < (rect.getWidth()-2*(it->first->GetWidth()+rect.getWDis())))
//				{
//				
//					wstring punEng = L"/.,\';][=-)(*&^%$#@!~`\"?><:}{";
//					wstring punChn = L"？》《“：}{|+——）（*&……%￥#@！~】【’；、。，";
//
//					if(punEng.find_first_of(sNex, 1) != wstring::npos ||
//						punChn.find_first_of(sNex, 1) != wstring::npos)
//					{
//						curPos.y += lineHeight[lineCounter++];
//						lineWidth = 0;
//						curPos.x = 0;
//					}
//				}
//			}
//			//
//			//add "-" into English words
//			//
//			if(lineWidth <= (rect.getWidth()-(it->first->GetWidth()+rect.getWDis())))
//			{
//
//				if(i > 0 && wcs[i] != 0	&& 
//					lineWidth > (rect.getWidth()-2*(it->first->GetWidth()+rect.getWDis())))
//				{
//					wstring sPre = L"";
//					sPre.push_back(wcs[i-1]);
//					SPString sP = (char *) _bstr_t(sPre.c_str());
//					setlocale(LC_ALL, "chs");
//					
//					if(sP.length() == 1 && s.length() == 1 && sP != " ")
//					{
//						SPFontPtr newFont = it->first;			
//						
//						pair<SPFontPtr, wstring> word1(newFont, L"-");
//						pair<pair<SPFontPtr, wstring>, D3DXVECTOR2> word2(word1, curPos);
//						lines[lineCounter].push_back(word2);
//						curPos.y += lineHeight[lineCounter++];
//						lineWidth = 0;
//						curPos.x = 0;
//						i--;
//					}
//					else
//					{
//						curPos.y += lineHeight[lineCounter++];
//						lineWidth = 0;
//						curPos.x = 0;
//						i--;
//					}
//				}
//				else
//				{
//					SPFontPtr newFont = it->first;
//
//					pair<SPFontPtr, wstring> word1(newFont, content);
//					pair<pair<SPFontPtr, wstring>, D3DXVECTOR2> word2(word1, curPos);
//					lines[lineCounter].push_back(word2);
//
//					if(newFont.get()->GetTextSize(s).y > lineHeight[lineCounter])
//					{
//						lineHeight[lineCounter] = newFont.get()->GetTextSize(s).y;
//					}
//
//					if(newFont.get()->GetTextSize(s).x == 0)
//					{
//						curPos.x += (newFont.get()->GetWidth()+rect.getWDis());
//						lineWidth += (newFont.get()->GetWidth()+rect.getWDis());
//					}
//					else
//					{
//						curPos.x += (newFont.get()->GetTextSize(s).x+rect.getWDis());
//						lineWidth += (newFont.get()->GetTextSize(s).x+rect.getWDis());
//					}
//				}
//			}
//			else
//			{
//				curPos.y += lineHeight[lineCounter++];
//				lineWidth = 0;
//				curPos.x = 0;
//				i--;
//			}
//		}
//	}*/
//
//	int maxHeight = 0;
//	for(int i = 0; i <= lineCounter; i++)
//	{
//		list<pair<pair<SPFontPtr, wstring>, D3DXVECTOR2>>::iterator it;
//		maxHeight += lineHeight[i];
//		
//		for(it = lines[i].begin(); it !=lines[i].end(); it++ )
//		{
//			SPString s = (char *) _bstr_t(it->first.second.c_str());
//			setlocale(LC_ALL, "chs");
//			if(it->second.y < maxHeight - it->first.first->GetTextSize(s).y)
//			{
//				it->second.y = maxHeight - it->first.first->GetTextSize(s).y;
//			}
//		}
//	}
//
//	for(int i = 0; i <= lineCounter; i++)
//	{
//		list<pair<pair<SPFontPtr, wstring>, D3DXVECTOR2>>::iterator it;
//		
//		for(it = lines[i].begin(); it !=lines[i].end(); it++ )
//		{
//			
//			SPString s = (char *) _bstr_t(it->first.second.c_str());
//			setlocale(LC_ALL, "chs");
//			SPFontWriter::GetSingleton().Write(it->first.first, NULL, s, it->second, SPColor::White, 0, NULL);
//		}
//	}
//
//
//	return true;
//}

//bool Test::textWriter(list<pair<SPFontPtr, SPString>> textList, textBox rect)
//{
//	D3DXVECTOR2 curPos(0, 0);
//	wstring text = L"";
//	int fontList[99];
//	int fontCounter = 0;
//
//	list<pair<SPFontPtr, SPString>>::iterator it;
//
//	//
//	//1. Put all SPString into a new one
//	//2. Get the relationship between each word in the new SPString and the font
//	//
//	for(it = textList.begin(); it != textList.end(); it++) 
//	{
//
//		/*strcpy(text, it->second.c_str());*/
//		/*strcat(text.c_str(), it->second.c_str());*/
//
//		wchar_t wcs[100];
//		setlocale(LC_CTYPE, ""); //很重要，没有这一句，转换会失败
//		mbstowcs(wcs, it->second.c_str(), it->second.length());
//		if(wcs[it->second.length()] != 0)
//			wcs[it->second.length()] = 0;
//		
//		int i = 0;
//		for(; i < it->second.length()+1; i++) 
//		{
//			text.push_back(wcs[i]);
//			if(wcs[i] == 0)
//				break;
//		}
//		fontList[fontCounter++] = i+1;		
//	}
//
//	//
//	//Get the height of each line
//	//
//	it = textList.begin();
//	int maxHeight[999] = {0};
//	int counter = 0;
//	int heightCounter = 0;
//
//	for(int k = 0; k < fontCounter; k++) 
//	{
//		for(int i = 0; i < fontList[k]; i++) 
//		{
//			if(curPos.x < rect.getWidth()) 
//			{
//
//				int max = it->first.get()->GetHeight() + rect.getLDis();
//				if(max > maxHeight[heightCounter]) 
//				{
//					maxHeight[heightCounter] = max;
//				}
//
//
//				SPString sPrevious = "";			
//				SPString s = (char *) _bstr_t(text.substr(counter, 1).c_str());
//				setlocale(LC_ALL, "chs");
//
//				int wordWidth = it->first.get()->GetTextSize(s).x + rect.getWDis();
//				int leftSpace = rect.getWidth() - wordWidth;
//
//				if(curPos.x > leftSpace	&& counter > 0 && curPos.x < rect.getWidth())
//				{
//
//					sPrevious = (char *) _bstr_t(text.substr((counter-1), 1).c_str());
//					if(sPrevious.size() == 1 && it->first.get()->GetTextSize(sPrevious).x != 0)
//					{
//						i--;
//						counter--;
//					}
//				}
//
//				if(it->first.get()->GetTextSize(s).x == 0) 
//				{
//					curPos.x += (it->first.get()->GetWidth() + rect.getWDis());
//				}
//				else 
//				{
//					curPos.x += (it->first.get()->GetTextSize(s).x + rect.getWDis());
//				}
//			}
//			else 
//			{
//				curPos.x = 0;
//				heightCounter++;
//			}
//
//			counter++;
//		}
//
//		it++;
//		if(it == textList.end())
//			break;
//	}
//
//	//
//	//render the words to the screen
//	//
//	it = textList.begin();
//	counter = 0;
//	heightCounter = 0;
//	int lineHeight = maxHeight[heightCounter];
//
//	curPos.x = 0;
//	curPos.y = lineHeight;
//
//	for(int k = 0; k < fontCounter; k++) 
//	{
//		for(int i = 0; i < fontList[k]; i++) 
//		{
//			curPos.y = (lineHeight - it->first.get()->GetHeight() - rect.getLDis());
//
//			SPRectangle place(curPos.x, curPos.y, 
//				it->first.get()->GetTextSize(it->second).x,
//				it->first.get()->GetTextSize(it->second).y);
//
//			SPString sPrevious = "";	
//			SPString sNext = "";
//			SPString s = (char *) _bstr_t(text.substr(counter, 1).c_str());
//			setlocale(LC_ALL, "chs");
//
//			int wordWidth = it->first.get()->GetTextSize(s).x + rect.getWDis();
//			int leftSpace = rect.getWidth() - wordWidth;
//
//			if(curPos.x <= rect.getWidth()-2*wordWidth)
//			{
//				SPFontWriter::GetSingleton().Write(it->first, NULL, s, place, SPColor::White, 0, NULL);
//				//test += s;
//				counter++;				
//			}
//			else if(/*(curPos.x <= leftSpace+rect.getWDis())
//				&& counter > 0 &&*/ curPos.x < leftSpace) 
//			{
//				
//				sPrevious = (char *) _bstr_t(text.substr((counter-1), 1).c_str());
//				if(counter < text.length())
//					sNext = (char *) _bstr_t(text.substr((counter+1), 1).c_str());
//				if(sPrevious.size() == 1 && it->first.get()->GetTextSize(sPrevious).x != 0
//					&& sNext.size() == 1 && it->first.get()->GetTextSize(sNext).x != 0)
//				{
//					SPFontWriter::GetSingleton().Write(it->first, NULL, "-", place, SPColor::White, 0, NULL);
//					i--;
//				}
//			}
//			else 
//			{
//				i--;
//			}
//			
//			
//				
//			if(curPos.x < rect.getWidth())
//			{
//				if(it->first.get()->GetTextSize(s).x == 0)
//				{
//					curPos.x += (it->first.get()->GetWidth() + rect.getWDis());
//				}
//				else 
//				{	
//					curPos.x += (it->first.get()->GetTextSize(s).x + rect.getWDis());
//				}
//			}
//			else 
//			{
//				curPos.x = 0;
//				lineHeight += (rect.getLDis() + maxHeight[++heightCounter]);
//			}
//			
//		}
//
//		it++;
//		if(it == textList.end())
//			break;
//	}
//
//	return true;
//}

bool Test::Load()
{
	logo = SPTextureManager::GetSingleton().GetTexture(L"a.png");
	tex = SPTextureManager::GetSingleton().GetTexture(L"a.png");
	blank = SPTextureManager::GetSingleton().GetTexture(L"blank.jpg");
	font = SPFontManager::GetSingleton().CreateFont(L"yh_101", 30, 0, 1, 5, false, L"微软雅黑");

	return true;
}

bool Test::Unload()
{
	//if (screenManager)
	//{
	//	screenManager->RemoveScreen(this);
	//	screenManager = NULL;
	//}

	return true;
}

bool Test::Initialize()
{
	return true;
}