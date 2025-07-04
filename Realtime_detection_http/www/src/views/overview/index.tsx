import usehookData from './hook'
import moment from 'moment'

function Home() {
	const {timeObj} = usehookData()
	return (
		<div className='m-auto p-16' style={{ maxWidth: '600px' }}>
			<div className='iframe my-20  flex justify-center' style={{ height: 'auto' }}>
				<video
					className='rounded-20'
					id='player'
					width='100%'
					muted
					autoPlay
					controls
				></video>
			</div>
			<div className='flex justify-between text-black opacity-60 mb-10'>
				<span>Time Stamp</span>
				<span>Delay</span>
			</div>

			<div className='flex justify-between text-17 '>
				<span>{moment(timeObj.time||0).format('YYYY-MM-DD hh:mm:ss')}</span>
				<span>{timeObj.delay}ms</span>
			</div>
		</div>
	)
}

export default Home
