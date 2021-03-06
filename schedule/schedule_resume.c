/* * 
 *  $Id: schedule_resume.c 80 2005-01-25 17:51:15Z federico $
 *  
 *  This file is part of Fenice
 *
 *  Fenice -- Open Media Server
 *
 *  Copyright (C) 2004 by
 *  	
 *	- Giampaolo Mancini	<giampaolo.mancini@polito.it>
 *	- Francesco Varano	<francesco.varano@polito.it>
 *	- Marco Penno		<marco.penno@polito.it>
 *	- Federico Ridolfo	<federico.ridolfo@polito.it>
 *	- Eugenio Menegatti 	<m.eu@libero.it>
 *	- Stefano Cau
 *	- Giuliano Emma
 *	- Stefano Oldrini
 * 
 *  Fenice is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  Fenice is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Fenice; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *  
 * */

// #include <time.h>
#include <sys/time.h>

#include <fenice/schedule.h>
#include <fenice/rtp.h>
#include <fenice/utils.h>

extern schedule_list sched[ONE_FORK_MAX_CONNECTION];

int schedule_resume(int id,play_args *args)
{
    struct timeval now;
    double mnow;

    gettimeofday(&now,NULL);

    mnow=(double)now.tv_sec*1000+(double)now.tv_usec/1000;
    
    sched[id].rtp_session->current_media->mstart_offset \
            +=  sched[id].rtp_session->current_media->mtime \
             - sched[id].rtp_session->current_media->mstart \
             + (double) sched[id].rtp_session->current_media->description.pkt_len;


    if (args->start_time_valid)
    sched[id].rtp_session->current_media->play_offset=args->start_time*1000;/*TODO:Federico. For Random Access*/

    sched[id].rtp_session->current_media->mstart = mnow;
    sched[id].rtp_session->current_media->mtime = sched[id].rtp_session->mprev_tx_time = mnow - (double) sched[id].rtp_session->current_media->description.pkt_len;
    sched[id].rtp_session->pause=0;

    return ERR_NOERROR;
}

