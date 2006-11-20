/*
 * Copyright (C) 2006 Apple Computer, Inc.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer. 
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution. 
 * 3.  Neither the name of Apple Computer, Inc. ("Apple") nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE AND ITS CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#import "WebContextMenuClient.h"

#import "WebElementDictionary.h"
#import "WebFrame.h"
#import "WebFrameInternal.h"
#import "WebHTMLView.h"
#import "WebHTMLViewInternal.h"
#import "WebNSPasteboardExtras.h"
#import "WebUIDelegate.h"
#import "WebView.h"
#import "WebViewInternal.h"
#import <WebCore/ContextMenu.h>
#import <WebCore/KURL.h>

using namespace WebCore;

PassRefPtr<WebContextMenuClient> WebContextMenuClient::create(WebView *webView)
{
    return new WebContextMenuClient(webView);
}

WebContextMenuClient::WebContextMenuClient(WebView *webView) 
    : m_webView(webView)
{
}

void WebContextMenuClient::ref() 
{
    Shared<WebContextMenuClient>::ref();
}

void WebContextMenuClient::deref()
{
    Shared<WebContextMenuClient>::deref();
}

void WebContextMenuClient::addCustomContextMenuItems(ContextMenu* menu)
{
    id delegate = [m_webView UIDelegate];
    if ([delegate respondsToSelector:@selector(webView:contextMenuItemsForElement:defaultMenuItems:)]) {
        NSDictionary *element = [[[WebElementDictionary alloc] initWithHitTestResult:menu->hitTestResult()] autorelease];
        NSArray *newMenu = [delegate webView:m_webView contextMenuItemsForElement:element defaultMenuItems:menu->platformMenuDescription()];
        menu->setPlatformMenuDescription(newMenu);
    }
}

void WebContextMenuClient::copyLinkToClipboard(HitTestResult hitTestResult)
{
    NSDictionary *element = [[[WebElementDictionary alloc] initWithHitTestResult:hitTestResult] autorelease];
    NSPasteboard *pasteboard = [NSPasteboard generalPasteboard];
    NSArray *types = [NSPasteboard _web_writableTypesForURL];
    [m_webView _writeLinkElement:element withPasteboardTypes:types toPasteboard:pasteboard];
}

void WebContextMenuClient::downloadURL(KURL url)
{
    [m_webView _downloadURL:url.getNSURL()];
}

void WebContextMenuClient::copyImageToClipboard(HitTestResult hitTestResult)
{
    NSDictionary *element = [[[WebElementDictionary alloc] initWithHitTestResult:hitTestResult] autorelease];
    NSPasteboard *pasteboard = [NSPasteboard generalPasteboard];
    NSArray *types = [NSPasteboard _web_writableTypesForImageIncludingArchive:(hitTestResult.innerNonSharedNode() != 0)];
    [[[element objectForKey:WebElementFrameKey] webView] _writeImageForElement:element 
                                                           withPasteboardTypes:types 
                                                                  toPasteboard:pasteboard];
}

void WebContextMenuClient::searchWithSpotlight()
{
    [m_webView _searchWithSpotlightFromMenu:nil];
}

void WebContextMenuClient::lookUpInDictionary(Frame* frame)
{
    WebHTMLView* htmlView = (WebHTMLView*)[[kit(frame) frameView] documentView];
    if(![htmlView isKindOfClass:[WebHTMLView class]])
        return;
    [htmlView _lookUpInDictionaryFromMenu:nil];
}
