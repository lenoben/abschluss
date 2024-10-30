import { logEvents } from './logEvents';
import { Request, Response, NextFunction } from 'express';

import { prisma } from '../controllers/database';

const errorHandler = async (
    err: Error,
    _req: Request,
    res: Response,
    _next: NextFunction,
) => {
    logEvents(`${err.name}: ${err.message}`, 'errLog.txt');
    await prisma.error_log.create({ data: {
        name: err.name,
        message: err.message,
        user_id: 1
    }})
    console.error(err.stack);
    res.status(500).send(err.message);
};

export default errorHandler;
