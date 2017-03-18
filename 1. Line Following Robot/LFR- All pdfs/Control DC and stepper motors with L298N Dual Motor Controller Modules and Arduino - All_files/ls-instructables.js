function ybWidth(){var e=(window,document),t=e.documentElement,i=Math.max(t.scrollWidth,t.offsetWidth,t.clientWidth);return i}function splitIndexSlots(){for(var e=new Array,t=new Array,i=0;i<index_slots.length;i++){var n=index_slots[i].split("_"),s=n.shift(),d=s,r=n.join("_");d==public_key?e.push(r):d==pmp_key&&t.push(r)}return[e,t]}function isSameSlot(e,t){return e=e.split("_"),t=t.split("_"),e.pop()==t.pop()&&e.pop()==t.pop()}function cygnus_index_judge(e){window.index_slots=[];for(var t={},i="^(?:"+public_key+"|"+pmp_key+")_(?:T([0-9])_)?(.*)_.*$",n=new RegExp(i),s=[],d=0;d<e.length;d++)if(e[d].split("_")[0]!==pmp_key){var r=n.exec(e[d]);if("undefined"!=typeof r&&null!==r){var o,a;if(o=r[1],a=r[2],"undefined"!=typeof o&&null!==o||(o=0),t[a]=t[a]||{},"undefined"==typeof t[a].tier||t[a].tier<o){t[a].tier=o;var _=e[d];if(o>0){var g=e[d].split("_"),h=g.shift(),l=g.join("_");g.shift();var p=g.join("_");_=h+"_"+p,_IndexRequestData.targetIDToBid[p]=_IndexRequestData.targetIDToBid[l]}t[a].target=_}}}else s.push(e[d]);var u=[];for(var c in t)t.hasOwnProperty(c)!==!1&&u.push(t[c].target);return u.concat(s)}function cygnus_augment_slots(){for(var e=cygnus_index_args.slots,t=e.length,i=0;t>i;i++){var n=e[i];n.siteID=cygnus_index_args.siteID;var s="T1_"+n.id;e.push({id:s,width:n.width,height:n.height,siteID:tierone2tiertwo[cygnus_index_args.siteID]})}cygnus_index_args.slots.push({id:"SQPS",width:300,height:250,siteID:cygnus_x1_args.SQPS_siteID}),cygnus_index_args.default_slots=cygnus_x1_args.default_slots,cygnus_index_args.default_bins=cygnus_x1_args.default_bins,cygnus_index_args.default_adcodes=cygnus_x1_args.default_adcodes}function cygnus_index_parse_res(e){try{if(window.index_slots=[],e){if("object"!=typeof _IndexRequestData||"object"!=typeof _IndexRequestData.impIDToSlotID||"undefined"==typeof _IndexRequestData.impIDToSlotID[e.id])return;var t,i=0;"object"==typeof _IndexRequestData.reqOptions&&"object"==typeof _IndexRequestData.reqOptions[e.id]&&("function"==typeof _IndexRequestData.reqOptions[e.id].callback&&(t=_IndexRequestData.reqOptions[e.id].callback),"number"==typeof _IndexRequestData.reqOptions[e.id].targetMode&&(i=_IndexRequestData.reqOptions[e.id].targetMode)),_IndexRequestData.lastRequestID=e.id;for(var n=[],s="undefined"==typeof e.seatbid?0:e.seatbid.length,d=0;s>d;d++)for(var r=0;r<e.seatbid[d].bid.length;r++){var o=e.seatbid[d].bid[r];if("object"==typeof o.ext&&"string"==typeof o.ext.pricelevel&&"undefined"!=typeof _IndexRequestData.impIDToSlotID[e.id][o.impid]){var a=_IndexRequestData.impIDToSlotID[e.id][o.impid];"undefined"==typeof index_slots&&(index_slots=[]),"undefined"==typeof _IndexRequestData.targetIDToBid&&(_IndexRequestData.targetIDToBid={});var _,g;"string"==typeof o.ext.dealid?(_=1===i?a+o.ext.pricelevel:a+"_"+o.ext.dealid,g=pmp_key+"_"):(_=a+o.ext.pricelevel,g=public_key+"_"),index_slots.push(g+_),void 0===_IndexRequestData.targetIDToBid[_]?_IndexRequestData.targetIDToBid[_]=[o.adm]:_IndexRequestData.targetIDToBid[_].push(o.adm);var h={};h.impressionID=o.impid,"undefined"!=typeof o.ext.dealid&&(h.dealID=o.ext.dealid),h.bid=o.price,h.slotID=a,h.priceLevel=o.ext.pricelevel,h.target=g+_,n.push(h)}}"function"==typeof t&&(0===n.length?t(e.id):t(e.id,n));var l=cygnus_index_sqps(),p=1;if(0>l&&(p=0),p){var u=Math.random();u<cygnus_index_stats.sampling.defaults&&cygnus_index_prepare_defaults(l)}window.index_slots=cygnus_index_judge(index_slots)}}catch(c){}"undefined"==typeof index_slots&&(index_slots=[]),cygnus_index_set_targets()}function headertag_render(e,t,i){e.write("Google sent targets: "+t+", with selector: "+i)}function index_render_default(e,t){var i="CasaleArgs = new Object();\nCasaleArgs.version = "+t.version+';\nCasaleArgs.adUnits = "'+t.adUnits+'";\nCasaleArgs.casaleID = '+t.casaleID+";\n";e.write("<script type='text/javascript'>"+i+"</script><script type='text/javascript' src='"+t.tag+"'></script>")}function index_render(e,t){if(index_activated_defaults.hasOwnProperty(public_key+"_"+t)){var i=index_activated_defaults[pmp_key+"_"+t];return index_render_default(e,i)}"undefined"==typeof index_demand&&(index_demand={});for(var n=t.split("_"),s=n[0],d=0;d<index_slots_render.length;d++)if("string"==typeof index_slots_render[d][public_key+"_"+t]){t=index_slots_render[d][public_key+"_"+t];var r=t.split("_");t=r[1]+"_"+r[2]+"_"+r[3],s=r[1]+"_"+r[2]}try{var o=_IndexRequestData.targetIDToBid[t].pop();null!=o?(e.write(o),index_demand[s]=1,delete index_no_demand[s]):index_headertag_lightspeed.analytics.send_null_creative_alert(cygnus_index_args.site_id,location.href,[t],index_headertag_lightspeed.correlator)}catch(a){}}function index_headertag_lightspeed_index_start(){function e(e){var t=d[e];return"string"==typeof t?t:"\\u"+("0000"+e.charCodeAt(0).toString(16)).slice(-4)}function t(t){return s.lastIndex=0,s.test(t)?t.replace(s,e):t}function i(e,t){if(this.initialized=!1,"number"!=typeof e||e%1!==0||0>e)throw"Invalid Site ID";if(this.siteID=e,this.impressions=[],this._parseFnName=void 0,top===self?(this.sitePage=location.href,this.topframe=1):(this.sitePage=document.referrer,this.topframe=0),"undefined"!=typeof t){if("function"!=typeof t)throw"Invalid jsonp target function";this._parseFnName="cygnus_index_args.parseFn"}"undefined"==typeof _IndexRequestData.requestCounter?_IndexRequestData.requestCounter=Math.floor(256*Math.random()):_IndexRequestData.requestCounter=(_IndexRequestData.requestCounter+1)%256,this.requestID=String((new Date).getTime()%2592e3*256+_IndexRequestData.requestCounter+256),this.initialized=!0}function n(e,t){if(t){var i=document.createElement("script");i.setAttribute("src",e),i.setAttribute("type","text/javascript");var n=document.getElementsByTagName("script")[0];n.parentNode&&n.parentNode.insertBefore(i,n)}else document.write('<script src="'+e+'"></script>')}index_headertag_lightspeed.cygnus_refresh_done=!1,index_headertag_lightspeed.bidder_timeouts.INDX=window.setTimeout(function(){index_headertag_lightspeed.cygnus_refresh_done||(index_headertag_lightspeed.cygnus_refresh_done=!0,index_headertag_lightspeed.log("INDX done at "+(Date.now()-index_headertag_lightspeed.start_time)),index_headertag_lightspeed.end_refresh("INDX"))},1e3),secondary_request&&(cygnus_index_args.embedMode=1),secondary_request=1,"undefined"==typeof index_no_demand&&(index_no_demand={}),index_slots_render=[],index_slots_add=[],targetID_to_slotID=[],index_activated_defaults={},cygnus_index_args.parseFn=cygnus_index_parse_res;var s=/[\\\"\x00-\x1f\x7f-\x9f\u00ad\u0600-\u0604\u070f\u17b4\u17b5\u200c-\u200f\u2028-\u202f\u2060-\u206f\ufeff\ufff0-\uffff]/g,d={"\b":"\\b","	":"\\t","\n":"\\n","\f":"\\f","\r":"\\r",'"':'\\"',"\\":"\\\\"};i.prototype.serialize=function(){var e='{"id":'+this.requestID+',"site":{"page":"'+t(this.sitePage)+'"';"string"==typeof document.referrer&&(e+=',"ref":"'+t(document.referrer)+'"'),e+='},"imp":[';for(var i=0;i<this.impressions.length;i++){var n=this.impressions[i],s=[];e+='{"id":"'+n.id+'", "banner":{"w":'+n.w+',"h":'+n.h+',"topframe":'+String(this.topframe)+"}","number"==typeof n.bidfloor&&(e+=',"bidfloor":'+n.bidfloor,"string"==typeof n.bidfloorcur&&(e+=',"bidfloorcur":"'+t(n.bidfloorcur)+'"')),"string"!=typeof n.slotID||n.slotID.match(/^\s*$/)||s.push('"sid":"'+t(n.slotID)+'"'),"number"==typeof n.siteID&&s.push('"siteID":'+n.siteID),s.length>0&&(e+=',"ext": {'+s.join()+"}"),e+=i+1==this.impressions.length?"}":"},"}return e+="]}"},i.prototype.setPageOverride=function(e){return"string"!=typeof e||e.match(/^\s*$/)?!1:(this.sitePage=e,!0)},i.prototype.addImpression=function(e,t,i,n,s,d){var r={id:String(this.impressions.length+1)};if("number"!=typeof e||1>=e)return null;if("number"!=typeof t||1>=t)return null;if(("string"==typeof s||"number"==typeof s)&&String(s).length<=50&&(r.slotID=String(s)),r.w=e,r.h=t,void 0!=i&&"number"!=typeof i)return null;if("number"==typeof i){if(0>i)return null;if(r.bidfloor=i,void 0!=n&&"string"!=typeof n)return null;r.bidfloorcur=n}if("undefined"!=typeof d){if(!("number"==typeof d&&d%1===0&&d>=0))return null;r.siteID=d}return this.impressions.push(r),r.id},i.prototype.sendRequestAsync=function(){if(0!=this.impressions.length&&this.initialized===!0){var e=encodeURIComponent(this.serialize()),t=("http:"===window.location.protocol,"http://as.casalemedia.com");return t+="/cygnus?v=7&fn=cygnus_index_parse_res&s="+this.siteID+"&r="+e,n(t,cygnus_index_args.embedMode),this.requestID}};try{if("undefined"==typeof cygnus_index_args||"undefined"==typeof cygnus_index_args.siteID||"undefined"==typeof cygnus_index_args.slots)return;"undefined"==typeof _IndexRequestData&&(_IndexRequestData={},_IndexRequestData.impIDToSlotID={},_IndexRequestData.reqOptions={});var r=new i(cygnus_index_args.siteID,cygnus_index_args.parseFn);cygnus_index_args.url&&"string"==typeof cygnus_index_args.url&&r.setPageOverride(cygnus_index_args.url),_IndexRequestData.impIDToSlotID[r.requestID]={},_IndexRequestData.reqOptions[r.requestID]={};var o,a;"undefined"!=typeof index_demand;for(var _=0;_<cygnus_index_args.slots.length;_++){if(o=cygnus_index_args.slots[_],"undefined"!=typeof index_demand&&"SQPS"!=o.id&&!(o.id in index_demand)){var g=0;if("undefined"==typeof index_no_demand[o.id]&&"SQPS"!=o.id)index_no_demand[o.id]=Date.now();else{var h=Date.now()-index_no_demand[o.id];h>15e3&&(g=1)}if(!g)continue;index_no_demand[o.id]=Date.now()}a=r.addImpression(o.width,o.height,o.bidfloor,o.bidfloorcur,o.id,o.siteID),a&&(_IndexRequestData.impIDToSlotID[r.requestID][a]=String(o.id))}return"number"==typeof cygnus_index_args.targetMode&&(_IndexRequestData.reqOptions[r.requestID].targetMode=cygnus_index_args.targetMode),"function"==typeof cygnus_index_args.callback&&(_IndexRequestData.reqOptions[r.requestID].callback=cygnus_index_args.callback),r.sendRequestAsync()}catch(l){}}function getSlotInfo(e){for(var t=0;t<cygnus_index_args.slots.length;t++){var i=cygnus_index_args.slots[t];if(i.id==e)return i}}function cygnus_index_prepare_defaults(e){for(var t={},i=0;i<cygnus_index_args.default_slots.length;i++)for(var n=cygnus_index_args.default_slots[i],s=0;s<index_slots.length;s++){var d=new RegExp("^[OP]_"+n+"_.*$");if(d.test(index_slots[s])){var r=index_slots[s].split("_");r[0],r[r.length-1];t[n]=1}}for(var i=0;i<cygnus_index_args.default_slots.length;i++){var n=cygnus_index_args.default_slots[i];if(!(n in t)){var o=cygnus_index_args.default_bins[e],a=cygnus_copy(cygnus_index_args.default_adcodes[o]),_=getSlotInfo(n),g=_.width+"x"+_.height,h=cygnus_index_adunits[g];if("undefined"!=typeof h){a.adUnits=String(h);var l=public_key+"_"+n+"_"+a.pricelevel;index_slot_to_size[l]=g,index_slots.push(l),index_activated_defaults[l]=a}}}}function cygnus_copy(e){var t=new Object;for(var i in e)e.hasOwnProperty(i)&&(t[i]=e[i]);return t}function cygnus_index_sqps(){function e(e){var t=e.split("_");if("SQPS"==t[1])return Number(t[2])}var t=-1;cygnus_index_args.sqps_slot="";for(var i=0;i<index_slots.length&&(t=e(index_slots[i]),cygnus_index_args.sqps_slot=index_slots[i],"undefined"==typeof t);i++);if("undefined"==typeof t||0>t)return-1;var n=-1;for(var s in cygnus_index_args.default_bins)cygnus_index_args.default_bins.hasOwnProperty(s)&&t>s&&s>n&&(n=s);return n>=0?n:-2}function save_targets(){for(var e=new Array,t=new Array,i=0;i<index_slots.length;i++){var n=index_slots[i].split("_"),s=n.shift(),d=s,r=n.join("_");d==public_key?e.push(r):d==pmp_key&&t.push(r)}e.length>0&&index_headertag_lightspeed.analytics.save_targets("INDX",public_key,e),t.length>0&&index_headertag_lightspeed.analytics.save_targets("INDX",pmp_key,t)}function cygnus_index_set_targets(){save_targets();var e=index_headertag_lightspeed.analytics.stop_timer("INDX");index_headertag_lightspeed.log("INDEX TOOK "+e+" ms."),index_headertag_lightspeed.cygnus_refresh_done||(index_headertag_lightspeed.cygnus_refresh_done=!0,index_headertag_lightspeed.end_refresh("INDX"))}function cygnus_index_set_div_based_targeting(e,t,i){for(var n=0;n<e.length;n++){var s=e[n].split("_"),d=s[0],r=cygnus_index_args.gpt_divs[d];if("undefined"!=typeof r)for(var o=0;o<r.length;o++){var a=r[o],_=i[a];if("undefined"!=typeof _){var g=_.getTargeting(t);g.push(e[n]),_.setTargeting(t,g)}}}}function cygnus_index_get_slot_size(e){for(var t=0;t<cygnus_index_args.slots.length;t++){var i=cygnus_index_args.slots[t];if(i.id===e)return[i.width,i.height]}return[null,null]}function cygnus_index_get_dfp_sizes(e){for(var t=e.getSizes(),i=[],n=0;n<t.length;n++)i.push([t[n].l,t[n].j]);return i}function cygnus_index_set_key_based_targeting(e,t,i){var n=cygnus_index_args.gpt_keymatch;for(var s in n)if(n.hasOwnProperty(s)===!0){var d=n[s];for(var r in i)if(i.hasOwnProperty(r)===!0){var o=i[r],a=o.getTargeting(s),_=cygnus_index_get_dfp_sizes(o);if(d.hasOwnProperty(a))for(var g=d[a],h=0;h<g.length;h++)for(var l=0;l<e.length;l++){var p=e[l].split("_"),u=p[0];if(g[h]==u)for(var c=cygnus_index_get_slot_size(u),f=0;f<_.length;f++){var y=_[f];if(y[0]==c[0]&&y[1]==c[1]){var m=o.getTargeting(t);m.push(e[l]),o.setTargeting(t,m)}}}}}}function load_script(e,t,i,n){var s=document.getElementsByTagName("script");if(!n)for(var d=0;d<s.length;d++){var r=s[d].src;if(r===e)return void t()}if(i){var o=s[0],a=document.createElement("script");a.setAttribute("src",e),a.setAttribute("type","application/javascript"),"string"==typeof t?a.setAttribute("callback",t):"function"==typeof t&&(a.onload=t),o.parentNode.insertBefore(a,o)}else{var _="<script type='text/javascript' src='"+e+"' callback='"+t+"'></script>";document.write(_)}}function inject_beacon(){var e="https"===window.location.protocol?"https://":"http://",t=Math.floor(9e3*Math.random()),i="instructables_auction_api",n="13390459",s="instructables.com",d="1.2",r=e+"gslbeacon.lijit.com/beacon?viewId="+i+"&rand="+t+"&informer="+n+"&type=fpads&loc="+s+"&v="+d;load_script(r,void 0,!0,!1)}function Bid(e){function t(e){switch(e){case 0:return"Pending";case 1:return"Bid available";case 2:return"Bid returned empty or error response";case 3:return"Bid timed out"}}this.bidderCode="",this.width=0,this.height=0,this.statusMessage=t(e)}function sovrn_slot_targeting(e){if(Array.isArray(e)){for(var t={},i=0;i<e.length;i++){var n=index_headertag_lightspeed.get_slot_id(e[i],"SOVRN");t[n]=e[i],e[i].setTargeting("sovrn_pb",""),e[i].setTargeting("sovrn_pid","")}e=t}for(var i=0;i<window.sovrn_bids.length;i++){var s,d=window.sovrn_bids[i],r=sovrn_price_flooring(d);"undefined"!=typeof e[d.impid]&&(s=parseFloat(e[d.impid].getTargeting("sovrn_pb")[0]||0),s>r||(e[d.impid].setTargeting("sovrn_pb",r),e[d.impid].setTargeting("sovrn_pid",d.placement_id+"_"+d.impid),window.sovrn_bid_creatives=window.sovrn_bid_creatives||{},window.sovrn_bid_creatives[d.placement_id]=window.sovrn_bid_creatives[d.placement_id]||{},window.sovrn_bid_creatives[d.placement_id][d.impid]={ad:d.ad,width:d.width,height:d.height}))}}function sovrn_save_targets(){for(var e=[],t=[],i=0;i<window.sovrn_bids.length;i++){var n=window.sovrn_bids[i];bid_cpm=sovrn_price_flooring(n),e.push(bid_cpm),t.push(n.placement_id)}index_headertag_lightspeed.analytics.save_targets("SOVRN","sovrn_pb",e),index_headertag_lightspeed.analytics.save_targets("SOVRN","sovrn_pid",t)}function refresh_sovrn(){var e="https"===window.location.protocol?"https://":"http://",t=e+"ap.lijit.com/rtb/bid?callback=sovrn_load_cb&br=";window.sovrn_count=window.sovrn_count||0;for(var i={id:"lv"+window.sovrn_count++,site:{domain:"instructables.com",page:document.location.pathname},imp:[]},n=0;n<window.sovrn_args.slots.length;n++){var s=window.sovrn_args.slots[n];i.imp.push({id:s.id+"-"+s.placement_id,banner:{w:s.width,h:s.height},tagid:s.placement_id})}t+=encodeURIComponent(JSON.stringify(i)),load_script(t,void 0,!0,!1)}window.headertagMobile=window.headertagMobile||!1,function(){function e(){this.start_time=Date.now(),this.hooks={},this.session_hooks={},this.request_counter=0,this.post_hooks_count={},this.post_hooks_completed_count={},this.correlator={},this.slot_targeting_hooks=[],this.dynacounter={},this.DEFAULT_NAMESPACE="initial-load",this.registered_bidders=[],this.bidder_complete={},this.bidder_timeouts={}}function t(e){return"function"==typeof e?!0:(this.log("Lightspeed hook is not a function: "+e),!1)}e.prototype.log=function(e){},e.prototype.warn=function(e){console.warn(e)},e.prototype.crit=function(e){console.error(e)},e.prototype.register_bidder=function(e){this.registered_bidders.push(e)},e.prototype.add_pre_refresh_hook=function(e,i,n,s){if("undefined"==typeof s&&(s=this.DEFAULT_NAMESPACE),t(i)){this.hooks[s]=this.hooks[s]||{};var d=this.hooks[s];d[e]=d[e]||{},d[e].pre_refresh=d[e].pre_refresh||[],i.oneshot=!!n,d[e].pre_refresh.push(i),this.log("Added pre-refresh hook for '"+e+"', hook:\n"+i.toString())}},e.prototype.add_post_refresh_hook=function(e,i,n,s){if("undefined"==typeof s&&(s=this.DEFAULT_NAMESPACE),t(i)){this.hooks[s]=this.hooks[s]||{};var d=this.hooks[s];this.post_hooks_count[s]=this.post_hooks_count[s]||0,d[e]=d[e]||{},d[e].post_refresh=d[e].post_refresh||[],i.oneshot=!!n,d[e].post_refresh.push(i),this.post_hooks_count[s]++,this.log("Added post-refresh hook for '"+e+"', hook:\n"+i.toString())}},e.prototype.add_session_start_hook=function(e,i,n){"undefined"==typeof n&&(n=this.DEFAULT_NAMESPACE),t(e)&&(e.oneshot=!!i,this.session_hooks[n]=this.session_hooks[n]||{start:[],finish:[]},this.session_hooks[n].start.push(e),this.log("Added session-start hook:\n"+e.toString()))},e.prototype.add_session_end_hook=function(e,i,n){"undefined"==typeof n&&(n=this.DEFAULT_NAMESPACE),t(e)&&(e.oneshot=!!i,this.session_hooks[n]=this.session_hooks[n]||{start:[],finish:[]},this.session_hooks[n].finish.push(e),this.log("Added session-end hook:\n"+e.toString()))},e.prototype.dynacounter_set=function(e,t,i){"undefined"==typeof i&&(i=this.DEFAULT_NAMESPACE),this.dynacounter[i]=this.dynacounter[i]||{};var n=this.dynacounter[i];n[e]=this.dynacounter[e]||{},n[e].enabled=!0,n[e].maxads=t,n[e].numads=0,this.log("Setup Dynamic ads Counter for technology: '"+e+"'. Maximum ads before canonical refresh end: "+t+".")},e.prototype.dynacounter_enable=function(e,t){"undefined"==typeof t&&(t=this.DEFAULT_NAMESPACE),this.dynacounter_set(e,0,t)},e.prototype.dynacounter_stall=function(e,t,i){"undefined"==typeof i&&(i=this.DEFAULT_NAMESPACE),this.dynacounter[i]=this.dynacounter[i]||{};var n=this.dynacounter[i];n[e]=n[e]||{},n[e].enabled=!0,n[e].maxads+=t,this.log("Stalling Dynamic ads Counter for technology: '"+e+"'. Stalled for "+t+" additional ads.")},e.prototype.dynacounter_tick=function(e,t){"undefined"==typeof t&&(t=this.DEFAULT_NAMESPACE);var i=this.dynacounter[t]||{};i[e].numads++,this.log("Dynamic ads Counter TICK for '"+e+"'. 1 Ads refreshed."),i[e].numads===i[e].maxads&&(i[e].enabled=!1,i[e].maxads=0,i[e].numads=0,this.log("Dynamic ads Counter TOCK for '"+e+"': ALL ADS READY."),this.end_refresh(e,t))},e.prototype.end_refresh=function(e,t){"undefined"==typeof t&&(t=this.DEFAULT_NAMESPACE);var i=this.session_hooks[t],n=this.hooks[t];if(this.bidder_complete[t][e]=!0,n.hasOwnProperty(e)){var s=n[e].post_refresh;if("undefined"!=typeof s)for(var d=0;d<s.length;d++)this.log("Executing post-refresh hook for '"+e+"', hook:\n"+s[d].toString()),s[d](this.correlator[t][d]),s[d].oneshot&&s.splice(d,1)}for(var r=!0,d=0;d<this.registered_bidders.length;d++){var e=this.registered_bidders[d];r&=this.bidder_complete[t][e]}if(r){this.bidder_complete[t]={},this.log("Session has completed. Running session end hooks.");for(var d=0;d<i.finish.length;d++){var o=i.finish[d];this.log("Executing session end hook:\n"+o.toString()),o(),i.finish[d].oneshot&&i.finish.splice(d,1)}}},e.prototype.refresh=function(e){"undefined"==typeof e&&(e=this.DEFAULT_NAMESPACE),this.bidder_complete[e]={},this.log("Refresh begin"),this.post_hooks_completed_count[e]=0,this.session_hooks[e]=this.session_hooks[e]||{start:[],finish:[]};for(var t=this.session_hooks[e],i=0;i<t.start.length;i++){var n=t.start[i];this.log("Executing session start hook:\n"+n.toString()),n(),t.start[i].oneshot&&t.start.splice(i,1)}var s=this.hooks[e];for(var d in s)if(s.hasOwnProperty(d)){var r=s[d].pre_refresh;if("undefined"!=typeof r)for(var i=0;i<r.length;i++)this.log("Executing pre-refresh hook for '"+d+"', hook:\n"+r[i].toString()),this.correlator[e]=this.correlator[e]||{},this.correlator[e][i]=r[i](),r[i].oneshot&&r.splice(i,1)}},e.prototype.add_slot_targeting_hook=function(e){this.slot_targeting_hooks.push(e)},e.prototype.set_slot_targeting=function(e){for(var t=0;t<this.slot_targeting_hooks.length;t++)this.slot_targeting_hooks[t](e)},e.prototype.generate_request_id=function(){var e=String((new Date).getTime()%2592e3*256+this.request_counter+256);return this.request_counter++,e},e.prototype.is_mobile=function(){var e=navigator.userAgent||navigator.vendor||window.opera;return!(!/(android|bb\d+|meego).+mobile|avantgo|bada\/|blackberry|blazer|compal|elaine|fennec|hiptop|iemobile|ip(hone|od)|iris|kindle|lge |maemo|midp|mmp|mobile.+firefox|netfront|opera m(ob|in)i|palm( os)?|phone|p(ixi|re)\/|plucker|pocket|psp|series(4|6)0|symbian|treo|up\.(browser|link)|vodafone|wap|windows ce|xda|xiino/i.test(e)&&!/1207|6310|6590|3gso|4thp|50[1-6]i|770s|802s|a wa|abac|ac(er|oo|s\-)|ai(ko|rn)|al(av|ca|co)|amoi|an(ex|ny|yw)|aptu|ar(ch|go)|as(te|us)|attw|au(di|\-m|r |s )|avan|be(ck|ll|nq)|bi(lb|rd)|bl(ac|az)|br(e|v)w|bumb|bw\-(n|u)|c55\/|capi|ccwa|cdm\-|cell|chtm|cldc|cmd\-|co(mp|nd)|craw|da(it|ll|ng)|dbte|dc\-s|devi|dica|dmob|do(c|p)o|ds(12|\-d)|el(49|ai)|em(l2|ul)|er(ic|k0)|esl8|ez([4-7]0|os|wa|ze)|fetc|fly(\-|_)|g1 u|g560|gene|gf\-5|g\-mo|go(\.w|od)|gr(ad|un)|haie|hcit|hd\-(m|p|t)|hei\-|hi(pt|ta)|hp( i|ip)|hs\-c|ht(c(\-| |_|a|g|p|s|t)|tp)|hu(aw|tc)|i\-(20|go|ma)|i230|iac( |\-|\/)|ibro|idea|ig01|ikom|im1k|inno|ipaq|iris|ja(t|v)a|jbro|jemu|jigs|kddi|keji|kgt( |\/)|klon|kpt |kwc\-|kyo(c|k)|le(no|xi)|lg( g|\/(k|l|u)|50|54|\-[a-w])|libw|lynx|m1\-w|m3ga|m50\/|ma(te|ui|xo)|mc(01|21|ca)|m\-cr|me(rc|ri)|mi(o8|oa|ts)|mmef|mo(01|02|bi|de|do|t(\-| |o|v)|zz)|mt(50|p1|v )|mwbp|mywa|n10[0-2]|n20[2-3]|n30(0|2)|n50(0|2|5)|n7(0(0|1)|10)|ne((c|m)\-|on|tf|wf|wg|wt)|nok(6|i)|nzph|o2im|op(ti|wv)|oran|owg1|p800|pan(a|d|t)|pdxg|pg(13|\-([1-8]|c))|phil|pire|pl(ay|uc)|pn\-2|po(ck|rt|se)|prox|psio|pt\-g|qa\-a|qc(07|12|21|32|60|\-[2-7]|i\-)|qtek|r380|r600|raks|rim9|ro(ve|zo)|s55\/|sa(ge|ma|mm|ms|ny|va)|sc(01|h\-|oo|p\-)|sdk\/|se(c(\-|0|1)|47|mc|nd|ri)|sgh\-|shar|sie(\-|m)|sk\-0|sl(45|id)|sm(al|ar|b3|it|t5)|so(ft|ny)|sp(01|h\-|v\-|v )|sy(01|mb)|t2(18|50)|t6(00|10|18)|ta(gt|lk)|tcl\-|tdg\-|tel(i|m)|tim\-|t\-mo|to(pl|sh)|ts(70|m\-|m3|m5)|tx\-9|up(\.b|g1|si)|utst|v400|v750|veri|vi(rg|te)|vk(40|5[0-3]|\-v)|vm40|voda|vulc|vx(52|53|60|61|70|80|81|83|85|98)|w3c(\-| )|webc|whit|wi(g |nc|nw)|wmlb|wonu|x700|yas\-|your|zeto|zte\-/i.test(e.substr(0,4)))},window.ix_ls_names=[],window.index_headertag_lightspeed=new e}(),function(){function e(){this.timers={},this.requestIDs=[],this.sessions={},this.targets={}}e.prototype.latest_request_id=function(){return this.requestIDs.length>0?this.requestIDs[this.requestIDs.length-1]:void 0},e.prototype.start_session=function(e){"undefined"==typeof e&&("undefined"!=typeof window.index_headertag_lightspeed&&"undefined"!=typeof window.index_headertag_lightspeed.generate_request_id?e=index_headertag_lightspeed.generate_request_id():index_headertag_lightspeed.log("Lightspeed not detected. You must provide generate the request ID manually.")),index_headertag_lightspeed.log("New request started: "+e),this.requestIDs.push(e),this.sessions[e]={started:Date.now(),ended:-1},this.timers[e]={}},e.prototype.end_session=function(e){"undefined"==typeof e&&(e=this.latest_request_id,"undefined"==typeof e&&index_headertag_lightspeed.log("Warning: tried to end a index_headertag_lightspeed session without ever having started one.")),this.sessions[e].ended=Date.now()},e.prototype.is_valid_request_id=function(e){return"undefined"==typeof e?!1:"undefined"==typeof this.timers[e]?!1:"undefined"!=typeof this.sessions[e]},e.prototype.start_timer=function(e){var t=this.latest_request_id();if(!this.is_valid_request_id(t))return void index_headertag_lightspeed.log("Timers must be correlated with a request session. Please start a new request session using index_headertag_lightspeed.analytics.start_session().");var i=Date.now();index_headertag_lightspeed.log("TIMER STARTED FOR "+e+" AT "+i),this.timers[t][e]={started:i}},e.prototype.peek_timer=function(e){var t=this.latest_request_id();if(!this.is_valid_request_id(t))return void index_headertag_lightspeed.log("Timers must be correlated with a request session. Please start a new request session using index_headertag_lightspeed.analytics.set_request_id().");var i=this.timers[t][e]?this.timers[t][e].started:void 0;if("undefined"!=typeof i){var n=this.timers[t][e]?this.timers[t][e].ended:Date.now();return n-i}},e.prototype.stop_timer=function(e){var t=this.latest_request_id();if(!this.is_valid_request_id(t))return void index_headertag_lightspeed.log("Timers must be correlated with a request session. Please start a new request session using index_headertag_lightspeed.analytics.set_request_id().");var i=this.timers[t][e]?this.timers[t][e].started:void 0;if("undefined"!=typeof i){var n=this.timers[t][e].ended;return"undefined"==typeof n?(n=Date.now(),index_headertag_lightspeed.log("TIMER ENDED FOR "+e+" AT "+n),this.timers[t][e].ended=n,n-i):n-i}},e.prototype.save_targets=function(e,t,i){var n=this.latest_request_id();return this.is_valid_request_id(n)?(this.targets[n]=this.targets[n]||{},this.targets[n][e]=this.targets[n][e]||{},void(this.targets[n][e][t]=i)):void index_headertag_lightspeed.log("Targeting reports must be correlated with a request session. Please start a new request session using index_headertag_lightspeed.analytics.set_request_id().")},e.prototype.send_null_creative_alert=function(e,t,i,n){var s="RT",d=(this.latest_request_id(),"?type="+s+"&r="+n+"&blank="+JSON.stringify(i)+"&s="+e+"&u="+encodeURIComponent(t)),r=new String;r+="http://as",r+=".casalemedia.com/headerstats"+d;var o=new Image;o.src=r,index_headertag_lightspeed.log("Sent Blank Creative Alert:\nurl: "+r+"\nParameters:\n"+r.split("&").slice(1).join("\n"))},e.prototype.create_report_query=function(e,t,i){var n="RT",s=this.latest_request_id(),d=this.sessions[s].started,r=this.sessions[s].ended||-1;if(!this.is_valid_request_id(s))return void index_headertag_lightspeed.log("Reports must be correlated with a request session. Please start a new request session using index_headertag_lightspeed.analytics.set_request_id().");var o="?type="+n+"&r="+i+"&t0="+d+"&t1="+r,a=this.timers[i],_=this.targets[i]||{},g=[];for(var h in a)a.hasOwnProperty(h)&&g.push(h);for(var l=0;l<g.length;l++){var h=g[l];if("undefined"!=typeof a[h]){var p=a[h].started||-1,u=a[h].ended||-1,c=u-p;c=c>0?c:-1;var f=-1,y=0;if(o+="&"+h+".t="+c+"&"+h+".ts="+f+"&"+h+".to="+y,"undefined"!=typeof _&&_.hasOwnProperty(h))for(var m in _[h]){var v=_[h][m],x="";if(v instanceof Array){for(var b=0;b<v.length-1;b++)x+=v[b]+",";x+=v[v.length-1]}else x=v;o+="&"+h+".p.pl."+m+"="+x}}}return o+"&s="+e+"&u="+encodeURIComponent(t)},e.prototype.send_report=function(e,t,i){var n=new String;n+="http://as",n+=".casalemedia.com/headerstats"+this.create_report_query(e,location.href,t,i);var s=new Image;s.src=n,index_headertag_lightspeed.log("Sent Report:\nurl: "+n+"\nParameters:\n"+n.split("&").slice(1).join("\n"))};var t=new e;"undefined"!=typeof window.index_headertag_lightspeed?index_headertag_lightspeed.analytics=t:window.index_headertag_lightspeed={analytics:t}}(),ybotq=[],window.ybot_mobile="desktop",ybWidth()>=481?window.ybot_mobile="desktop":window.ybot_mobile="mobile",/.*/.test(location.href)&&/-1/.test(document.cookie.indexOf("hideAds"))&&(window.cygnus_index_args={name:"cygnus",embedMode:1,siteID:167730,slots:[{id:"1",width:728,height:90,siteID:167730},{id:"2",width:970,height:250,siteID:174896},{id:"3",width:300,height:250,siteID:174897},{id:"4",width:300,height:600,siteID:174898},{id:"7",width:300,height:250,siteID:174901},{id:"8",width:300,height:250,siteID:174902},{id:"9",width:300,height:250,siteID:174903},{id:"10",width:300,height:600,siteID:174904}],gpt_divs:{1:["gpt-ad-leaderboard"],2:["gpt-ad-leaderboard"],3:["gpt-ad-med-rectangle"],4:["gpt-ad-med-rectangle"],7:["gpt-ad-inline-med-1"],8:["gpt-ad-inline-med-2"],9:["gpt-ad-sidebar-brand"],10:["gpt-ad-sidebar-brand"]}},window.trinity_args={"gpt-ad-leaderboard":"68189f114565bd6b96ce","gpt-ad-med-rectangle":"abfff7dacc2c65d0dcd6","gpt-ad-sidebar-brand":"6e9426bf35cfe227e140","gpt-ad-inline-med-1":"211701bf355a6918c0c2","gpt-ad-inline-med-2":"62d06d585ba2ccd01cdf"},window.sovrn_args={name:"sovrn",custom_pricelevels:[{cpm:20,granularity:.05}],slots:[{id:"gpt-ad-leaderboard",width:"970",height:"250",placement_id:355725},{id:"gpt-ad-leaderboard",width:"728",height:"90",placement_id:355728},{id:"gpt-ad-med-rectangle",width:"300",height:"600",placement_id:355729},{id:"gpt-ad-med-rectangle",width:"300",height:"250",placement_id:355730},{id:"gpt-ad-sidebar-brand",width:"300",height:"600",placement_id:355731},{id:"gpt-ad-inline-med-2",width:"300",height:"250",placement_id:355733},{id:"gpt-ad-inline-med-1",width:"300",height:"250",placement_id:355734},{id:"gpt-ad-sidebar-brand",width:"300",height:"250",placement_id:355735}]}),/true/.test(/.*m\..*/.test(location.href)||headertagMobile)&&/-1/.test(document.cookie.indexOf("hideAds"))&&(window.cygnus_index_args={name:"cygnus",embedMode:1,siteID:167730,slots:[{id:"5",width:320,height:50,siteID:174899},{id:"6",width:320,height:100,siteID:174900},{id:"11",width:300,height:250,siteID:174905},{id:"12",width:300,height:250,siteID:174906},{id:"13",width:300,height:250,siteID:174907}],gpt_divs:{5:["gpt-ad-m"],6:["gpt-ad-m"],11:["gpt-ad-m-rect"],12:["gpt-ad-m-inline"],13:["gpt-bottom1_m"]}},window.trinity_args={"gpt-ad-m":"7d15c985564f445de317","gpt-ad-m-rect":"0d851f03b80fae5e1912","gpt-ad-m-inline":"8ef9750836a37b21c7a8"},window.sovrn_args={name:"sovrn",custom_pricelevels:[{cpm:20,granularity:.05}],slots:[{id:"gpt-ad-m",width:"320",height:"100",placement_id:355736},{id:"gpt-ad-m",width:"320",height:"50",placement_id:355737},{id:"gpt-ad-m-rect",width:"300",height:"250",placement_id:355739},{id:"gpt-ad-m-inline",width:"300",height:"250",placement_id:355743}]}),/true/.test(/.*[^m]\.instructables\.com*/.test(location.href)&&!headertagMobile)&&(window.ls_ybot_active_config={name:"ybot",async:"true",site_code:"56c9",slots:[{id:"LB"},{id:"MR"},{id:"MR2"}]},ybotq.push(function(){yieldbot.pub("56c9"),yieldbot.enableAsync(),yieldbot.defineSlot("LB"),yieldbot.defineSlot("MR"),yieldbot.defineSlot("MR2"),yieldbot.go()})),/true/.test(/.*m\..*/.test(location.href)||headertagMobile)&&(window.ls_ybot_active_config={name:"ybot",async:"true",site_code:"4752",slots:[{id:"MLB"},{id:"mobrec"}]},ybotq.push(function(){yieldbot.pub("4752"),yieldbot.enableAsync(),yieldbot.defineSlot("MLB"),yieldbot.defineSlot("mobrec"),yieldbot.go()})),index_headertag_lightspeed.register_bidder("INDX"),window.googletag=window.googletag||{},googletag.cmd=googletag.cmd||[];var cygnus_tid=4,public_key="O",pmp_key="P",cygnus_index_stats={sampling:{defaults:1}},cygnus_index_adunits={"728x90":2,"120x600":3,"300x250":4,"160x600":5,"336x280":6,"234x60":7,"300x600":8,"300x50":9,"320x50":10,"970x250":12,"300x1050":13,"970x90":14,"180x150":15},tierone2tiertwo={160242:164103},secondary_request=0,index_slot_to_size={};index_headertag_lightspeed.add_slot_targeting_hook(function(e){window.index_slots=window.index_slots||[];var t=splitIndexSlots(),i=t[0],n=t[1];if(Array.isArray(e)&&"undefined"!=typeof cygnus_index_args.gpt_divs){for(var s={},d=0;d<e.length;d++){var r=e[d].getSlotElementId();s[r]=e[d]}e=s}var o="undefined"==typeof cygnus_index_args.gpt_divs?cygnus_index_set_key_based_targeting:cygnus_index_set_div_based_targeting;i.length>0&&o(i,public_key,e),n.length>0&&o(n,pmp_key,e)}),index_headertag_lightspeed.add_pre_refresh_hook("INDX",function(){index_headertag_lightspeed.analytics.start_timer("INDX"),index_headertag_lightspeed_index_start()}),index_headertag_lightspeed.add_post_refresh_hook("INDX",function(){
window.clearTimeout(index_headertag_lightspeed.bidder_timeouts.INDX)}),index_headertag_lightspeed.add_session_end_hook(function(){"function"==typeof window.cygnus_index_ready_state&&window.cygnus_index_ready_state()}),window.ybotq=window.ybotq||[],function(){var e=document.createElement("script");e.src="//cdn.yldbt.com/js/yieldbot.intent.js";var t=document.getElementsByTagName("script")[0];t.parentNode.insertBefore(e,t)}(),window.ix_ls_names.push("YBOT"),index_headertag_lightspeed.register_bidder("yieldbot"),index_headertag_lightspeed.add_pre_refresh_hook("yieldbot",function(){console.log("YBOT Refresh"),index_headertag_lightspeed.analytics.start_timer("YBOT"),index_headertag_lightspeed.bidder_timeouts.YBOT=setTimeout(function(){index_headertag_lightspeed.end_refresh("yieldbot")},1e3),ybotq.push(function(){var e=yieldbot.getPageCriteria();console.log("YBOT Got targeting: "+JSON.stringify(e)),"function"==typeof googletag.cmd.unshift?googletag.cmd.unshift(function(){googletag.pubads().setTargeting("ybot",e)}):googletag.cmd.push(function(){googletag.pubads().setTargeting("ybot",e)}),index_headertag_lightspeed.analytics.save_targets("YBOT","ybot",e),index_headertag_lightspeed.end_refresh("yieldbot")})}),index_headertag_lightspeed.add_post_refresh_hook("yieldbot",function(){clearTimeout(index_headertag_lightspeed.bidder_timeouts.YBOT),index_headertag_lightspeed.analytics.stop_timer("YBOT")}),index_headertag_lightspeed.register_bidder("SBI"),function(e,t){function i(){var t=window[e];for(var i in t)if(t.hasOwnProperty(i))for(var n in t[i])t[i].hasOwnProperty(n)&&index_headertag_lightspeed.analytics.save_targets("SBI",i+"."+n,t[i][n])}function n(e){if("undefined"==typeof e){var e={},i=googletag.pubads.getSlots();if("undefined"==typeof i)return;for(var n=0;n<e.length;n++)slot=i[n],e[slot.getSlotElementId()]=slot}if(Array.isArray(e)){for(var s={},n=0;n<e.length;n++){var d=e[n].getSlotElementId();s[d]=e[n]}e=s}window[t]=e,window.googletag=window.googletag||{},googletag.cmd=googletag.cmd||[];var r=function(){index_headertag_lightspeed.trinity_loaded||index_headertag_lightspeed.log("Sonobi Trinity missed the auction.");var e=window[t];for(var i in sbi_trinity)if(sbi_trinity.hasOwnProperty(i)!==!1)if(e.hasOwnProperty(i)!==!1){var n=e[i];if(sbi_trinity.hasOwnProperty(i))for(var s in sbi_trinity[i])n.setTargeting(s,sbi_trinity[i][s])}else index_headertag_lightspeed.log("Could not set SBI targeting on slot '"+i+"' because it has not been defined.")};"undefined"!=typeof googletag.cmd.unshift?googletag.cmd.unshift(r):googletag.cmd.push(r)}function s(){index_headertag_lightspeed.analytics.start_timer("SBI");var e="https"===window.location.protocol?"https://":"http://",t=document.createElement("script");t.type="text/javascript",t.src=e+"apex.go.sonobi.com/trinity.js?key_maker="+JSON.stringify(d),t.onload=function(){index_headertag_lightspeed.trinity_loaded=!0,index_headertag_lightspeed.log("TRINITY done at "+(Date.now()-index_headertag_lightspeed.start_time)),index_headertag_lightspeed.end_refresh("SBI")};var i=document.getElementsByTagName("script")[0];i.parentNode.insertBefore(t,i),index_headertag_lightspeed.bidder_timeouts.SBI=setTimeout(function(){index_headertag_lightspeed.end_refresh("SBI")},1e3)}var d=window.trinity_args;index_headertag_lightspeed.add_pre_refresh_hook("SBI",s,!1),index_headertag_lightspeed.add_slot_targeting_hook(n,!1),index_headertag_lightspeed.add_post_refresh_hook("SBI",function(){i(),clearTimeout(index_headertag_lightspeed.bidder_timeouts.SBI),index_headertag_lightspeed.analytics.stop_timer("SBI")})}("sbi_trinity","dfp_slots"),window.ix_ls_names.push("SOVRN"),window.sovrn_bids=[];var sovrn_price_flooring=function(e){for(var t=window.sovrn_args.custom_pricelevels,i=e.cpm,n=0;n<t.length;n++){var s=1/t[n].granularity;if(i<t[n].cpm){var d=(Math.floor(i*s)/s).toFixed(2);return d}}var d=Number(t[t.length-1].cpm).toFixed(2);return d};window.sovrn_load_cb=function(e){var t={};window.sovrn_bids=[];for(var i=0;i<window.sovrn_args.slots.length;i++){var n=window.sovrn_args.slots[i],s=n.id+"-"+n.placement_id;t[s]=n}if(e&&e.id){e.seatbid&&0!==e.seatbid.length&&e.seatbid[0].bid&&0!==e.seatbid[0].bid.length&&e.seatbid[0].bid.forEach(function(e){var i,n="",s=e.impid,d=t[s];if(d&&(n=d.placement_id,d.status="good",i=parseFloat(e.price),0!==i)){e.placement_id=n,e.size=d.width+"x"+d.height;var r=e.adm,o='<img src="'+e.nurl+'">';bid=new Bid(1),bid.creative_id=e.id,bid.placement_id=e.placement_id,bid.bidderCode="SOVRN",bid.cpm=i,bid.adid=e.adid,bid.ad=decodeURIComponent(r+o),bid.width=d.width,bid.height=d.height,bid.impid=d.id,bid.bidnum=window.sovrn_count,window.sovrn_bids.push(bid)}})}index_headertag_lightspeed.end_refresh("SOVRN")},index_headertag_lightspeed.add_post_refresh_hook("SOVRN",function(){index_headertag_lightspeed.analytics.stop_timer("SOVRN"),sovrn_save_targets()}),index_headertag_lightspeed.add_pre_refresh_hook("SOVRN",function(){index_headertag_lightspeed.analytics.start_timer("SOVRN"),refresh_sovrn()}),index_headertag_lightspeed.add_slot_targeting_hook(sovrn_slot_targeting),inject_beacon(),sovrn_render=function(e,t){var i,n=t.split("_"),s=n[0],d=n.splice(1).join("_");"undefined"!=typeof window.sovrn_bid_creatives[s]&&"undefined"!=typeof window.sovrn_bid_creatives[s][d]&&(i=window.sovrn_bid_creatives[s][d],"undefined"!=typeof i.ad&&(e.write(i.ad),e.defaultView&&e.defaultView.frameElement&&(e.defaultView.frameElement.width=i.width,e.defaultView.frameElement.height=i.height)))},index_headertag_lightspeed.corrleator={},index_headertag_lightspeed.add_session_start_hook(function(){index_headertag_lightspeed.correlator["initial-load"]=index_headertag_lightspeed.generate_request_id(),index_headertag_lightspeed.analytics.start_session(index_headertag_lightspeed.correlator["initial-load"])},!1,"initial-load"),index_headertag_lightspeed.add_session_end_hook(function(){index_headertag_lightspeed.analytics.end_session(index_headertag_lightspeed.correlator["initial-load"]),index_headertag_lightspeed.analytics.send_report(cygnus_index_args.siteID,index_headertag_lightspeed.correlator["initial-load"])},!1,"initial-load"),index_headertag_lightspeed.add_session_end_hook(function(){googletag.cmd.push(function(){var e=function(){for(var e=googletag.pubads().getSlots(),t={},i=0;i<e.length;i++)t[e[i].getSlotElementId()]=e[i];index_headertag_lightspeed.set_slot_targeting(t);for(var i=0;i<e.length;i++)googletag.display(e[i].getSlotElementId())};"loading"===document.readyState?document.addEventListener("DOMContentLoaded",function(t){e()}):e()})}),/-1/.test(document.cookie.indexOf("hideAds"))&&index_headertag_lightspeed.refresh();