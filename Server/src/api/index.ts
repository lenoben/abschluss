import { Router } from 'express';
const router = Router();
import v1 from './v1';
import { senml } from '../middleware/auth';

router.use('/v1', senml);
router.use('/v1', v1);

export default router;
